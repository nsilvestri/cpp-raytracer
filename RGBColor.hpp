#pragma once

class RGBColor
{
    private:
        float r;
        float g;
        float b;
    public:
        RGBColor(float r, float g, float b);
        RGBColor();
        RGBColor(const RGBColor& obj);
        ~RGBColor();
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
};

