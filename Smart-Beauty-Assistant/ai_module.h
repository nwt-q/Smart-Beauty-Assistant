#ifndef AI_MODULE_H
#define AI_MODULE_H

#include <QObject>

class Ai_Module : public QObject
{
    Q_OBJECT
public:
    explicit Ai_Module(QObject *parent = nullptr);

signals:
};

#endif // AI_MODULE_H
