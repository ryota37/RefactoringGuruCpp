
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

// The Strategy interface declares operations common to all supported versions of some algorithm.
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual std::string doAlgorithm(std::string_view data) const = 0;
};

// The Context defines the interface of interest to clients.
class Context
{
private:
    std::unique_ptr<Strategy> strategy_;
public:
    explicit Context(std::unique_ptr<Strategy> &&strategy = {}) : strategy_(std::move(strategy))
    {
    }
    void set_strategy(std::unique_ptr<Strategy> &&strategy)
    {
        strategy_ = std::move(strategy);
    }
    void doSomeBusinessLogic() const
    {
        if(strategy_) {
            std::cout << "Context: Sorting data using the strategy(not sure how it'll do it)" << std::endl;
            std::string result = strategy_->doAlgorithm("aecbd");
            std::cout << result << std::endl;
        } else {
            std::cout << "Context: Strategy isn't set" << std::endl;
        }
    }
};

// Concrete Strategies implement the algorithm while following the base Strategy interface.
// The Interface makes them interchangeable in the Context.
class ConcreteStrategyA : public Strategy
{
public:
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result));
        
        return result;
    }
};
class ConcreteStrategyB : public Strategy
{
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result), std::greater<>());

        return result;
    }
};

// The client code picks a concrete strategy and passes it to the context.
// The client should be aware of the differences between strategies in order to make the right choice.
void clientCode()
{
    Context context(std::make_unique<ConcreteStrategyA>());
    std::cout << "Client: Strategy is set to normal sorting." << std::endl;
    context.doSomeBusinessLogic();
    std::cout << std::endl;
    std::cout << "Client: Strategy is set to reverse sorting." << std::endl;
    context.set_strategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();
}

int main()
{
    clientCode();
    return 0;
}