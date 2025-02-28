
**Adapter** is a structural design pattern that allows objects with incompatible interfaces to collaborate.

## Problem

Imagine that you’re creating a stock market monitoring app. The app downloads the stock data from multiple sources in XML format and then displays nice-looking charts and diagrams for the user.

At some point, you decide to improve the app by integrating a smart 3rd-party analytics library. But there’s a catch: the analytics library only works with data in JSON format.
![screen](./images/6.1.png)

## Solution
You can create an _adapter_. This is a special object that converts the interface of one object so that another object can understand it.

An adapter wraps one of the objects to hide the complexity of conversion happening behind the scenes. The wrapped object isn’t even aware of the adapter. For example, you can wrap an object that operates in meters and kilometers with an adapter that converts all of the data to imperial units such as feet and miles.

Adapters can not only convert data into various formats but can also help objects with different interfaces collaborate. Here’s how it works:
1. The adapter gets an interface, compatible with one of the existing objects.
2. Using this interface, the existing object can safely call the adapter’s methods.
3. Upon receiving a call, the adapter passes the request to the second object, but in a format and order that the second object expects.

Sometimes it’s even possible to create a two-way adapter that can convert the calls in both directions.
![screen](./images/6.2.png)


## Structure

![screen](./images/6.3.png)

1-The **Client** is a class that contains the existing business logic of the program.
2-The **Client Interface** describes a protocol that other classes must follow to be able to collaborate with the client code.
3-The **Service** is some useful class (usually 3rd-party or legacy). The client can’t use this class directly because it has an incompatible interface.
4-The **Adapter** is a class that’s able to work with both the client and the service: it implements the client interface, while wrapping the service object. The adapter receives calls from the client via the client interface and translates them into calls to the wrapped service object in a format it can understand.
5-The client code doesn’t get coupled to the concrete adapter class as long as it works with the adapter via the client interface. Thanks to this, you can introduce new types of adapters into the program without breaking the existing client code. This can be useful when the interface of the service class gets changed or replaced: you can just create a new adapter class without changing the client code.

### Implementation of the Adapter Pattern in C++ Design Patterns:

Let’s say you are working on a new project that uses a modern logging system, but you have a legacy library with a different logging interface. You can use the Adapter pattern to make the legacy system compatible with the new system.

Step 1: Define the Target Interface (what the new system expects)
```c++
class ILogger {
public:
    virtual void logInfo(const std::string &message) = 0;
    virtual void logError(const std::string &message) = 0;
    virtual ~ILogger() = default;
};
```

#### Step 2: Define the Legacy Logger (Adaptee)

This is the existing logger system that cannot be changed.
```c++
class LegacyLogger {
public:
    void writeToLog(const std::string &message) {
        std::cout << "Legacy Log: " << message << std::endl;
    }
};
```

Step 3: Create the Adapter
The adapter makes the `LegacyLogger` compatible with the `ILogger` interface.
```c++
class LoggerAdapter : public ILogger {
private:
    LegacyLogger &legacyLogger; // Reference to the legacy logger

public:
    LoggerAdapter(LegacyLogger &logger) : legacyLogger(logger) {}

    void logInfo(const std::string &message) override {
        legacyLogger.writeToLog("INFO: " + message);
    }

    void logError(const std::string &message) override {
        legacyLogger.writeToLog("ERROR: " + message);
    }
};

```
Step 4: Use the Adapter in the Client Code
Now, the client can use the adapter, unaware that it’s using a legacy system behind the scenes.
```c++
int main() {
    LegacyLogger legacyLogger;
    LoggerAdapter adapter(legacyLogger);

    adapter.logInfo("This is an information message");
    adapter.logError("This is an error message");
    return 0;
}

```