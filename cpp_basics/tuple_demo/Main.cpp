#include <mutex>
#include <thread>
#include <iostream>

#include "Demo.h"
#include "TupleMembers.h"
#include "ReferenceTester.h"


int main()
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);

    ////////////////////////////////////////////////////////////////////////////////
    // size of empty tuple
    ////////////////////////////////////////////////////////////////////////////////
    {
        std::tuple<> empty;
        auto emtpySize = sizeof(empty); // 1
        std::cout << "size of empty tuple  : " << emtpySize << std::endl;
    }
    std::cout << std::endl;

    ////////////////////////////////////////////////////////////////////////////////
    // get
    ////////////////////////////////////////////////////////////////////////////////
    std::cout << "# demo for get ############################" << std::endl;
    {
        auto values = std::make_tuple<std::string, uint32_t>("Johnny", 22);
        std::cout << "name  : " << std::get<0>(values) << std::endl;
        std::cout << "age   : " << std::get<1>(values) << std::endl;
    }
    std::cout << std::endl;

    ////////////////////////////////////////////////////////////////////////////////
    // clone
    ////////////////////////////////////////////////////////////////////////////////
    std::cout << "# demo for copy construction ##############" << std::endl;
    {
        auto values = std::make_tuple<std::string, uint32_t>("Johnny", 22);
        std::tuple<std::string, uint32_t> valuesClone = values;
        std::cout << "name  : " << std::get<0>(valuesClone) << std::endl;
        std::cout << "age   : " << std::get<1>(valuesClone) << std::endl;
    }
    std::cout << std::endl;

    ////////////////////////////////////////////////////////////////////////////////
    // tuple as class member
    ////////////////////////////////////////////////////////////////////////////////
    std::cout << "# demo as a class member ##################" << std::endl;
    {
        TupleMembers<std::string, uint8_t, bool> members("Jhonny", 10, true);
        std::cout << "name  : " << std::get<0>(members.myMembers) << std::endl;
        std::cout << "age   : " << std::get<1>(members.myMembers) << std::endl;
        std::cout << "alive : " << std::get<2>(members.myMembers) << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "# demo for call ###########################" << std::endl;
    {
        TupleMembers<std::string, uint8_t, bool> members("Jhonny", 10, true);
        members.CallFirstArg([](std::string& name) {
            std::cout << "Called : " << name << std::endl;
        });
        members.CallWithHelper([](std::string& name, uint8_t age, bool alive) {
            std::cout << "Called : " << name << " with " << age << " and is " << (
                alive ? "alive": "dead"
            ) << std::endl; 
        });
    }
    std::cout << std::endl;
    
    ////////////////////////////////////////////////////////////////////////////////
    // references of tuple
    ////////////////////////////////////////////////////////////////////////////////
    std::cout << "# demo for tuple references ###############" << std::endl;
    ReferenceTester::Reset();
    {
        ReferenceTester ref1;
        ReferenceTester ref2;
        ReferenceTester::PrintStatus("tuple init");

        auto refs = std::make_tuple<ReferenceTester, ReferenceTester>(std::move(ref1), std::move(ref2));
        ReferenceTester::PrintStatus("tuple created");

        std::cout << "get id 1st time : " << std::get<0>(refs).myID << std::endl;
        std::cout << "get id 2nd time : " << std::get<0>(refs).myID << std::endl;
        ReferenceTester::PrintStatus("tuple print");
    }
    ReferenceTester::PrintStatus("tuple - done");
    std::cout << std::endl;

    ////////////////////////////////////////////////////////////////////////////////
    // references of members
    ////////////////////////////////////////////////////////////////////////////////
    std::cout << "# demo for tuple member references ##########" << std::endl;
    ReferenceTester::Reset();
    {
        ReferenceTester ref;
        ReferenceTester::PrintStatus("members init");

        TupleMembers<ReferenceTester> members(ref);
        ReferenceTester::PrintStatus("members created");

        std::cout << "get id 1st time : " << std::get<0>(members.myMembers).myID << std::endl;
        ReferenceTester::PrintStatus("members print");
    }
    ReferenceTester::PrintStatus("members - done");
    std::cout << std::endl;

    return 0;
}
