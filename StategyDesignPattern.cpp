#include <iostream>

class Strategy {
 public:
  virtual void execute() = 0;
};

class ConcreteStrategyA : public Strategy {
 public:
  void execute() override {
    std::cout << "Executing algorithm A" << std::endl;
  }
};

class ConcreteStrategyB : public Strategy {
 public:
  void execute() override {
    std::cout << "Executing algorithm B" << std::endl;
  }
};

class Context {
 private:
  Strategy* strategy;

 public:
  Context(Strategy* strategy) : strategy(strategy) {}

  void setStrategy(Strategy* strategy) {
    this->strategy = strategy;
  }

  void executeStrategy() {
    strategy->execute();
  }
};

int main() {
  Context context(new ConcreteStrategyA());
  context.executeStrategy();
  context.setStrategy(new ConcreteStrategyB());
  context.executeStrategy();
  return 0;
}
