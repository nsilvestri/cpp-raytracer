#pragma once

#include <iostream>

class RGBColor
{
    private:
        float r;
        float g;
        float b;
    public:
        RGBColor();
        RGBColor(float r, float g, float b);
        RGBColor(const RGBColor& obj);

        float getLuminance() const;
        void scale(float scale);

        float getR() const;
        float getG() const;
        float getB() const;
        void setR(float r);
        void setG(float g);
        void setB(float b);
        void setRGB(float r, float g, float b);
        
        static float clamp(float f);

        
        friend std::ostream& operator<<(std::ostream& stream, const RGBColor& r);
};

