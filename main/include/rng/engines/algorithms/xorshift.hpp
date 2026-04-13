#include "../rng.hpp"

class Xorshift : public RNG {
private:
    uint32_t state;
    uint32_t initialState;
public:
    explicit Xorshift(int seed);
    uint64_t generate() override;
    void reset() override;
    std::string getName() const override { return "XORSHIFT"; }
};