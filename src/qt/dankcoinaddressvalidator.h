// Copyright (c) 2011-2014 The Dankcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DANKCOIN_QT_DANKCOINADDRESSVALIDATOR_H
#define DANKCOIN_QT_DANKCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class DankcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DankcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Dankcoin address widget validator, checks for a valid dankcoin address.
 */
class DankcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DankcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // DANKCOIN_QT_DANKCOINADDRESSVALIDATOR_H
