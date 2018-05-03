// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MB8COIN_QT_MB8COINADDRESSVALIDATOR_H
#define MB8COIN_QT_MB8COINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class MB8CoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MB8CoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** MB8Coin address widget validator, checks for a valid mb8coin address.
 */
class MB8CoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MB8CoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // MB8COIN_QT_MB8COINADDRESSVALIDATOR_H
