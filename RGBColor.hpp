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
        ~RGBColor();
        float getLuminance();
        void scale(float scale);
        float getR();
        float getG();
        float getB();
        void setR(float r);
        void setG(float g);
        void setB(float b);
        void setRGB(float r, float g, float b);
        static float clamp(float f);
};

