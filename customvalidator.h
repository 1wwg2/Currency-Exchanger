#ifndef CUSTOMVALIDATOR_H
#define CUSTOMVALIDATOR_H

#include <QDoubleValidator>

class CustomValidator : public QDoubleValidator
{
public:
     CustomValidator(QObject* parent = nullptr);
     QValidator::State validate(QString &input, int &pos) const override;
     ~CustomValidator();
};

#endif // CUSTOMVALIDATOR_H
