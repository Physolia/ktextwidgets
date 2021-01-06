/*
    SPDX-FileCopyrightText: 2014 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "kpluralhandlingspinbox.h"

class KPluralHandlingSpinBoxPrivate
{
public:
    KPluralHandlingSpinBoxPrivate(QSpinBox *q)
        : q(q)
    {
        QObject::connect(q, SIGNAL(valueChanged(int)), q, SLOT(updateSuffix(int)));
    }

    void updateSuffix(int value)
    {
        if (!pluralSuffix.isEmpty()) {
            KLocalizedString s = pluralSuffix;
            q->setSuffix(s.subs(value).toString());
        }
    }

    QSpinBox *const q;
    KLocalizedString pluralSuffix;
};


KPluralHandlingSpinBox::KPluralHandlingSpinBox(QWidget *parent)
    : QSpinBox(parent),
      d(new KPluralHandlingSpinBoxPrivate(this))
{
}

KPluralHandlingSpinBox::~KPluralHandlingSpinBox() = default;

void KPluralHandlingSpinBox::setSuffix(const KLocalizedString &suffix)
{
    d->pluralSuffix = suffix;
    if (suffix.isEmpty()) {
        QSpinBox::setSuffix(QString());
    } else {
        d->updateSuffix(value());
    }
}
#include "moc_kpluralhandlingspinbox.cpp"
