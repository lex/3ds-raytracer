class Vec3 {
    float x;
    float y;
    float z;

    public:
        Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
              float operator[](const size_t i)       { return i == 0 ? x : i == 1 ? y : z; }
        const float operator[](const size_t i) const { return i == 0 ? x : i == 1 ? y : z; }
};
