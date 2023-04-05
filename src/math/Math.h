
#define EPSILON 0.00000001f

class Math
{
public:
    static bool IsZero(float value) { return (value > -EPSILON) && (value < EPSILON); }
};