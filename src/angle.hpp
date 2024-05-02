#pragma once

class Angle {
    public:
        Angle(float val);
        float val;
        bool is0();
        bool is45();
        bool is90();

    private:
        const float ERROR_TOLERANCE = 0.05;
};
