#pragma once

#include <string>
#include <memory>
#include "common/math.h"

//!
//! class Opera hhh
//!     a class to manipulate the procedure of Opera
//!
class Opera {
public:

    //! Create the opera (in .h)
    Opera();

    //! Destroy the opera (in .h)
    virtual ~Opera();

    //! Start the opera
    //! @brief Show info about starting of the opera
    //! @exception none
    //! @see SceneOperator::Start()
    void Start();

    //! Stop the opera
    //! @fn void Opera::Stop(aCondition)
    //! @brief ~~Show info about stopping of the opera~~
    //! @brief Those started with @ are [special commands](https://www.doxygen.nl/manual/commands.html)
    //! - [Markdown is supported](https://www.doxygen.nl/manual/markdown.html)
    //!   - a list is OK
    //!   - a list is supported
    void Stop();

private:
    std::shared_ptr<Operator> __operator;   //!< Description after a member
};

