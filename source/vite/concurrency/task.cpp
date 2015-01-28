/**
* The MIT License (MIT)
*
* Copyright (c) 2015 Abi George Ullattil (Vite Falcon)

* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#pragma once

#include "task.h"
#include "../ioc/ioc.h"
#include "../exception.hpp"
#include "../exception/boost_error_detail.h"

#include <sstream>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>

#include <tbb/task.h>

namespace vite
{
    vDEFINE_EXCEPTION_WIH_NAMESPACE(TaskException, tasks);

    Task::Task(const TaskId& id)
        : mId(id)
    {
    }

    class TbbTask : public tbb::task
    {
    private:
        TaskPtr task;
        Variant args;
    public:
        TbbTask(TaskPtr task, Variant&& args)
            : task(task)
            , args(args)
        {
            vTHROW_IF(!this->task, IllegalArgumentException() << ErrorInfoDetail("Task should not be null/empty."))
        }

        virtual tbb::task* execute() override
        {
            try
            {
                task->run(args);
            }
            catch (::boost::exception& ex)
            {
                vTHROW(tasks::TaskException() << ErrorInfoDetail("Failed to run task") << boost::BoostExceptionInfo(ex));
            }
            catch (std::exception& ex)
            {
                vTHROW(tasks::TaskException() << ErrorInfoDetail("Failed to run task") << ErrorInfoCausedBy(ex));
            }
            catch (...)
            {
                vTHROW(tasks::TaskException() << ErrorInfoDetail("Failed to run task due to an unknown exception!"));
            }
            return nullptr;
        }
    };
    typedef TbbTask* TbbTaskPtr;

    class TbbTaskBuilder;
    typedef std::shared_ptr<TbbTaskBuilder> TbbTaskBuilderPtr;

    class TbbTaskBuilder
    {
    private:
        const TaskPtr task;

    public: // static
        static TbbTaskBuilderPtr ForTask(const TaskPtr& task)
        {
            return std::make_shared<TbbTaskBuilder>(task);
        }

    public:
        TbbTaskBuilder(const TaskPtr& task) : task(task) {}

        ~TbbTaskBuilder() = default;

        TbbTaskPtr buildForArgs(Variant&& args)
        {
            return new (tbb::task::allocate_root()) TbbTask(task, std::move(args));
        }
    };

    struct TaskInfo
    {
        std::string name;
        TaskId id;
        TbbTaskBuilderPtr taskBuilder;
    };

    using namespace ::boost::multi_index;

    class TaskFactoryImpl : public TaskFactory
    {
        struct TaskNameTag {};
        struct TaskIdTag {};

        typedef member<TaskInfo, std::string, &TaskInfo::name> TaskInfoName;
        typedef member<TaskInfo, TaskId, &TaskInfo::id> TaskInfoId;
        typedef indexed_by <
            hashed_unique<tag<TaskNameTag>, TaskInfoName>,
            hashed_non_unique<tag<TaskIdTag>, TaskInfoId> > IndexedBy;
        typedef ::boost::multi_index_container <TaskInfo, IndexedBy> ContainerType;
        typedef ContainerType::index<TaskNameTag>::type TaskNameIndex;
        typedef ContainerType::index<TaskIdTag>::type TaskIdIndex;

        ContainerType mTasks;
    public:
        virtual TaskId registerTask(const std::string& name, TaskPtr task) override
        {
            if (mTasks.get<TaskNameTag>().count(name) != 0)
            {
                std::stringstream errorMessage;
                errorMessage << "A task with name '" << name << "' already exists!";
                vTHROW(InvalidOperationException() << ErrorInfoDetail(errorMessage.str()));
            }
            else if (!task)
            {
                std::stringstream errorMessage;
                errorMessage << "The task given (named '" << name << "') is empty!";
                vTHROW(InvalidOperationException() << ErrorInfoDetail(errorMessage.str()));
            }
            TaskId id = task->getId();
            TaskInfo taskInfo = { name, task->getId(), TbbTaskBuilder::ForTask(task) };
            mTasks.insert(taskInfo);
            return id;
        }

        virtual void scheduleTask(const TaskId& taskId, Variant&& args) override
        {
            TaskIdIndex& taskIndex = mTasks.get<TaskIdTag>();
            auto taskIdItr = taskIndex.find(taskId);
            if (taskIdItr == taskIndex.end())
            {
                std::stringstream errorMessage;
                errorMessage << "No task with ID " << taskId << " was found.";
                vTHROW(ItemNotFoundException() << ErrorInfoDetail(errorMessage.str()));
            }
            scheduleTbbTask(taskIdItr->taskBuilder, std::move(args));
        }

        virtual void scheduleTaskNamed(const std::string& name, Variant&& args) override
        {
            TaskNameIndex& taskIndex = mTasks.get<TaskNameTag>();
            auto taskNameItr = taskIndex.find(name);
            if (taskNameItr == taskIndex.end())
            {
                std::stringstream errorMessage;
                errorMessage << "No task with name '" << name << "' was found.";
                vTHROW(ItemNotFoundException() << ErrorInfoDetail(errorMessage.str()));
            }
            scheduleTbbTask(taskNameItr->taskBuilder, std::move(args));
        }

        inline void scheduleTbbTask(TbbTaskBuilderPtr taskBuilder, Variant&& args)
        {
            auto tbbTask = taskBuilder->buildForArgs(std::move(args));
            tbb::task::spawn(*tbbTask);
        }

        virtual void runTask(const TaskId& taskId, Variant&& args) override
        {
            throw std::logic_error("The method or operation is not implemented.");
        }

        virtual void runTaskNamed(const std::string& name, Variant&& args) override
        {
            throw std::logic_error("The method or operation is not implemented.");
        }

    };

    const std::string TaskFactory::INSTANCE_NAME = InstanceOf::ForClass<TaskFactory>().useInstanceOf<TaskFactoryImpl>();

    TaskFactory& TaskFactory::GetInstance()
    {
        return InstanceOf::Get<TaskFactory>(INSTANCE_NAME);
    }

}