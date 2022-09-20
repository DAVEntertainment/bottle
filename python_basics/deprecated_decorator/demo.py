from dec import deprecated, deprecated_with_info, deprecated_after

@deprecated
def test_deprecated():
    print("calling test_deprecated")
    
@deprecated_with_info("will be removed in 3.0.1")
def test_deprecated_with_info():
    print("calling test_deprecated_with_info")


@deprecated_after(3, 0, 1)
def test_deprecated_after():
    print("calling test_deprecated_after")


def main():
    print("calling main")
    print("")
    test_deprecated()
    print("")
    test_deprecated_with_info()
    print("")
    test_deprecated_after()
    print("")

if "__main__" == __name__:
    main()
