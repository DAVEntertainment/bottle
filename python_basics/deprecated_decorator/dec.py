def deprecated(func):
    def wrapped():
        print("deprecated wrapper")
        func()
    return wrapped

def deprecated_with_info(message):
    def nested_dep(func):
        def wrapped():
            print("deprecated_with_info wrapper")
            print(message)
            func()
        return wrapped
    return nested_dep

def deprecated_after(major = 0, minor = 0, build = 0):
    def nested_dep(func):
        def wrapped():
            print("deprecated_after wrapper")
            print("will be deprecated after {}.{}.{}".format(major, minor, build))
            func()
        return wrapped
    return nested_dep
