#ifndef NORMALIZATIONPARAMETERS_H
#define NORMALIZATIONPARAMETERS_H

class NormalizationParameters
{
public:
    NormalizationParameters(double _min,double _max): min(_min), max(_max){};
    double min;
    double max;
    static double normalValue(double min,double max,double value,double from,double to) {
        return from + (value - min) / (max - min) * (to - from);
    }
};

#endif // NORMALIZATIONPARAMETERS_H
