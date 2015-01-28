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

#include "../defines.hpp"
#include "../optional.hpp"
#include "../named_variants.hpp"
#include "task_id.h"

namespace vite
{
    class vLIB_EXPORT Task
    {
    public:
        Task(const TaskId& id);

        virtual ~Task() = default;

        virtual void run(const Variant& args) = 0;

        vINLINE TaskId getId() const
        {
            return mId;
        }

    private:
        const TaskId mId;
    };

    typedef std::shared_ptr<Task> TaskPtr;

    template <typename ArgumentType>
    class TaskImpl : public Task
    {
    public:
        typedef std::unique_ptr<TaskImpl> TaskPtr;
        typedef std::function<void(const ArgumentType&)> FunctionType;

        TaskImpl(const TaskId& id, FunctionType&& callback) : Task(id), mCallback(callback) {}
        ~TaskImpl() = default;

        virtual void run(const Variant& variantArgs) override
        {
            const ArgumentType args = variantArgs.as<ArgumentType>();
            mCallback(args);
        }

    private:
        const FunctionType mCallback;
    };

    class vLIB_EXPORT TaskFactory
    {
    public: // static
        static const std::string INSTANCE_NAME;

        static TaskFactory& GetInstance();

    public:
        virtual TaskId registerTask(const std::string& name, TaskPtr task) = 0;

        virtual void scheduleTask(const TaskId& taskId, Variant&& args) = 0;
        virtual void scheduleTaskNamed(const std::string& name, Variant&& args) = 0;

        virtual void runTask(const TaskId& taskId, Variant&& args) = 0;
        virtual void runTaskNamed(const std::string& name, Variant&& args) = 0;

    protected:
        TaskFactory() = default;
        virtual ~TaskFactory() = default;
    };
}