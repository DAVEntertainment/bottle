# Demo
Demo of C++ shared_ptr thread safe only in use_count scope

The result of expirenment is positive,
shared_ptr's use_count mechanics is thread-safe

According to https://www.zhihu.com/question/56836057,
there's still risk of thread-safe problem.

So at least my examples are not good enough to reveal the problems.

Just be careful to use shared_ptr in multi-threading situations.

# How to build & run
Just run `test.cmd`
