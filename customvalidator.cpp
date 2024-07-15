#include "customvalidator.h"

CustomValidator::CustomValidator(QObject* parent) : QDoubleValidator(parent)
{

}

QValidator::State CustomValidator::validate(QString &input, int &pos) const
{
    if(input.contains('E') || input.contains('e'))
    {
        return QValidator::Invalid;
    }
    else
    {
        return QDoubleValidator::validate(input, pos);
    }
}

CustomValidator::~CustomValidator()
{

}
