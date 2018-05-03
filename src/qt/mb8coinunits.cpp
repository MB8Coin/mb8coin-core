// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "mb8coinunits.h"

#include "primitives/transaction.h"
#include "util.h"

#include <math.h>

#include <QStringList>
#include <QSettings>

#include <sstream>
#include <string>
#include <iomanip>

MB8CoinUnits::MB8CoinUnits(QObject *parent):
        QAbstractListModel(parent),
        unitlist(availableUnits())
{
}

QList<MB8CoinUnits::Unit> MB8CoinUnits::availableUnits()
{
    QList<MB8CoinUnits::Unit> unitlist;
    unitlist.append(MB8);
//    unitlist.append(mMB8);
//    unitlist.append(uMB8);
    unitlist.append(BTC);
    unitlist.append(EUR);
    unitlist.append(USD);
    return unitlist;
}

bool MB8CoinUnits::valid(int unit)
{
    switch(unit)
    {
    case MB8:
//    case mMB8:
//    case uMB8:
    case BTC:
    case EUR:
    case USD:
        return true;
    default:
        return false;
    }
}

QString MB8CoinUnits::name(int unit)
{
    switch(unit)
    {
    case MB8: return QString("MB8");
//    case mMB8: return QString("mMB8");
//    case uMB8: return QString::fromUtf8("μMB8");
    case BTC: return QString::fromUtf8("BTC");
    case EUR: return QString::fromUtf8("EUR");
    case USD: return QString::fromUtf8("USD");
    default: return QString("???");
    }
}

QString MB8CoinUnits::description(int unit)
{
    switch(unit)
    {
    case MB8: return QString("MB8Coins");
//    case mMB8: return QString("Milli-MB8Coins (1 / 1" THIN_SP_UTF8 "000)");
//    case uMB8: return QString("Micro-MB8Coins (1 / 1" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
    case BTC: return QString("BTC");
    case EUR: return QString("Euro");
    case USD: return QString("US Dolar");
    default: return QString("???");
    }
}

qint64 MB8CoinUnits::factor(int unit)
{

    QSettings settings;

    switch(unit)
    {
    case MB8:  return 100000000;
//    case mMB8: return 100000;
//    case uMB8: return 100;
    case BTC:  return settings.value("btcFactor", 0).toFloat();
    case EUR:  return settings.value("eurFactor", 0).toFloat();
    case USD:  return settings.value("usdFactor", 0).toFloat();
    default:   return 100000000;
    }
}

int MB8CoinUnits::decimals(int unit)
{
    switch(unit)
    {
    case MB8: return 8;
//    case mMB8: return 5;
//    case uMB8: return 2;
    case BTC: return 8;
    case EUR: return 6;
    case USD: return 6;
    default: return 0;
    }
}

QString MB8CoinUnits::format(int unit, const CAmount& nIn, bool fPlus, SeparatorStyle separators)
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    if(!valid(unit))
        return QString(); // Refuse to format invalid unit
    qint64 n = (qint64)nIn;
    qint64 coin = factor(unit);
    int num_decimals = decimals(unit);
    qint64 n_abs = (n > 0 ? n : -n);
    double quotient;
    qint64 remainder;

    quotient = n_abs / coin;

    std::ostringstream out;
    out << std::setprecision(num_decimals) << std::fixed
        << std::showpoint << (double)n_abs / (double)coin;
    std::istringstream in(out.str());
    std::string wholePart;
    std::getline(in, wholePart, '.');
    in >> remainder;

    QString quotient_str = QString::number((qint64)quotient);
    QString remainder_str = QString::number(remainder).rightJustified(num_decimals, '0');

    // Use SI-style thin space separators as these are locale independent and can't be
    // confused with the decimal marker.
    QChar thin_sp(THIN_SP_CP);
    int q_size = quotient_str.size();
    if (separators == separatorAlways || (separators == separatorStandard && q_size > 4))
        for (int i = 3; i < q_size; i += 3)
            quotient_str.insert(q_size - i, thin_sp);

    if (n < 0)
        quotient_str.insert(0, '-');
    else if (fPlus && n > 0)
        quotient_str.insert(0, '+');

    return quotient_str + QString(".") + remainder_str;
}


// NOTE: Using formatWithUnit in an HTML context risks wrapping
// quantities at the thousands separator. More subtly, it also results
// in a standard space rather than a thin space, due to a bug in Qt's
// XML whitespace canonicalisation
//
// Please take care to use formatHtmlWithUnit instead, when
// appropriate.

QString MB8CoinUnits::formatWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    return format(unit, amount, plussign, separators) + QString(" ") + name(unit);
}

QString MB8CoinUnits::formatHtmlWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    QString str(formatWithUnit(unit, amount, plussign, separators));
    str.replace(QChar(THIN_SP_CP), QString(THIN_SP_HTML));
    return QString("<span style='white-space: nowrap;'>%1</span>").arg(str);
}


bool MB8CoinUnits::parse(int unit, const QString &value, CAmount *val_out)
{
    if(!valid(unit) || value.isEmpty())
        return false; // Refuse to parse invalid unit or empty string
    int num_decimals = decimals(unit);

    // Ignore spaces and thin spaces when parsing
    QStringList parts = removeSpaces(value).split(".");

    if(parts.size() > 2)
    {
        return false; // More than one dot
    }
    QString whole = parts[0];
    QString decimals;

    if(parts.size() > 1)
    {
        decimals = parts[1];
    }
    if(decimals.size() > num_decimals)
    {
        return false; // Exceeds max precision
    }
    bool ok = false;
    QString str = whole + decimals.leftJustified(num_decimals, '0');

    if(str.size() > 18)
    {
        return false; // Longer numbers will exceed 63 bits
    }
    CAmount retvalue(str.toLongLong(&ok));
    if(val_out)
    {
        *val_out = retvalue;
    }
    return ok;
}

QString MB8CoinUnits::getAmountColumnTitle(int unit)
{
    QString amountTitle = QObject::tr("Amount");
    if (MB8CoinUnits::valid(unit))
    {
        amountTitle += " ("+MB8CoinUnits::name(unit) + ")";
    }
    return amountTitle;
}

int MB8CoinUnits::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return unitlist.size();
}

QVariant MB8CoinUnits::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row >= 0 && row < unitlist.size())
    {
        Unit unit = unitlist.at(row);
        switch(role)
        {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return QVariant(name(unit));
        case Qt::ToolTipRole:
            return QVariant(description(unit));
        case UnitRole:
            return QVariant(static_cast<int>(unit));
        }
    }
    return QVariant();
}

CAmount MB8CoinUnits::maxMoney()
{
    return MAX_MONEY;
}
