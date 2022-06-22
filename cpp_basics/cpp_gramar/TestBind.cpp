#include <gtest/gtest.h>

#include <functional>
#include <iostream>
#include <memory>

namespace details {
    class MessageBase
    {};

    class TestMessage1 :
        public MessageBase
    {
    public:
        int myData = 10;
    };

    class MessageNotification :
        public MessageBase
    {
    public:
        std::string                         myNotification;
    };
}

TEST(Bind, DynamicClassType)
{
    details::TestMessage1 m1;
    m1.myData = 10;

    decltype(m1) m2;
    m2 = m1;

    EXPECT_EQ(m1.myData, m2.myData);
}

TEST(Bind, FunctionConversion)
{
    std::function<void(const details::MessageBase&)> a = []
    (const details::MessageBase& m) {
        std::cout << "common message" << std::endl;
    };
    std::function<void(const details::TestMessage1&)> b = []
    (const details::TestMessage1& m) {
        std::cout << "test message " << m.myData << std::endl;
    };
    details::MessageBase m1;
    details::TestMessage1 m2;
    m2.myData = 12;

    a(m1);
    b(m2);

    // /* can not be compiled */
    //std::function<void(const details::MessageBase&)> c =
    //  (std::function<void(const details::MessageBase&)>)b;
    //c(m2);

    std::function<void(const details::TestMessage1&)> d =
        (std::function<void(const details::TestMessage1&)>) a;

    EXPECT_NO_THROW(d(m2));
};


namespace details {

    class MessageProcessor :
        public std::enable_shared_from_this<MessageProcessor>
    {
    public:
        void
        OnMessageGetCurrentThreadID(
            MessageNotification&                            aMessage
        )
        {
            std::cout << "MessageProcessor : " + aMessage.myNotification << std::endl;
            myNotification = aMessage.myNotification;
        }

        void
        OnMessageGetCurrentThreadIDWithComment(
            MessageNotification&                            aMessage,
            std::string&                                    aComment
        )
        {
            std::cout << "MessageProcessor : " + aMessage.myNotification + "(" + aComment + ")" << std::endl;
            myNotification = aMessage.myNotification;
        }

        std::string
        GetNotification()
        {
            return myNotification;
        }
    private:
        std::string                         myNotification;
    };

}

TEST(Bind, BindSharedPointer)
{
    details::MessageNotification notification;
    notification.myNotification = __FUNCTION__;

    details::MessageProcessor* p = nullptr;
    {
        std::function<void(details::MessageNotification)> handler;
        {
            auto tempProcessor = std::make_shared<details::MessageProcessor>();
            handler = std::bind(
                &details::MessageProcessor::OnMessageGetCurrentThreadID,
                tempProcessor,
                std::placeholders::_1
            );
            p = tempProcessor.get();
        }
        handler(notification);
        std::cout << "Notification = " + p->GetNotification() << std::endl;
    }
    try {
        std::cout << "Notification (again) = " + p->GetNotification() << std::endl; // will generate a runtime error
    } catch (std::bad_alloc& err) {
        std::cout << "Got exception : " + std::string(err.what()) << std::endl;
    }
}


namespace details {

    class BindProvider :
        public std::enable_shared_from_this<BindProvider>
    {
    public:
        void
        Func()
        {
            std::cout << "BindProvider::Func" << std::endl;
            myExecuted = true;
        }
        bool                        myExecuted = false;
    };

    template<typename FuncType, typename ClassType>
    void
    _BindFun(
        typename FuncType                       aFunction,
        std::weak_ptr<ClassType>&               aObject
    )
    {
        if (auto locked = aObject.lock()) {
            auto execFun = std::bind(
                aFunction,
                locked.get()
            );
            execFun();
        }
    };

    template<typename FuncType, typename ClassType>
    std::function<void(void)>
    Bind(
        FuncType                                aFunction,
        std::weak_ptr<ClassType>&               aObject
    ) {
        return std::bind(
            &_BindFun<FuncType, ClassType>,
            aFunction,
            aObject
        );
    };
}

TEST(Bind, Binder)
{
    auto provider = std::make_shared<details::BindProvider>();

    auto handler = details::Bind(
        &details::BindProvider::Func,
        provider->weak_from_this()
    );

    handler();

    EXPECT_EQ(provider->myExecuted, true);
}

