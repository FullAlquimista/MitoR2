#include "../include/mitor/sql/validarentrada.hpp"

bool validarCPF(QString cpf)
{
    if(cpf.isEmpty() || cpf.count() > 11)
        return false;

    QString tmp(cpf);
    int DV[2] = {0};

    // Calculo do primeiro digito.
    tmp.truncate(9);
    auto itC = tmp.rbegin();
    int mul = 2;
    QVector<int> soma;
    for(; itC != tmp.rend(); ++itC) {
        QChar c = *itC;
        if(c.isDigit()) {
            int d = c.digitValue();
            int res = d * mul++;
            soma.push_front(res);
        }else
            return false;
    }
    int somatoria = 0;
    for(auto i : soma) somatoria += i;
    int r = (somatoria > 0 ? somatoria % 11 : 0);
    DV[1] = (r < 2 ? 0 : 11 - r);
    tmp = tmp.append(QString("%1").formatArg(DV[1]));

    // Calculo do segundo digito.
    itC = tmp.rbegin();
    mul = 2;
    soma.clear();
    for(; itC != tmp.rend(); ++itC) {
        QChar c = *itC;
        if(c.isDigit()) {
            int d = c.digitValue();
            int res = d * mul++;
            soma.push_front(res);
        }else
            return false;
    }
    somatoria = 0;
    for(auto i : soma) somatoria += i;
    r = (somatoria > 0 ? somatoria % 11 : 0);
    DV[0] = (r < 2 ? 0 : 11 - r);
    tmp = tmp.append(QString("%1").formatArg(DV[0]));

    if(cpf == tmp)
        return true;

    return false;
}

bool validarCNPJ(QString cnpj)
{
    if(cnpj.isEmpty() || cnpj.count() > 15)
        return false;

    QString tmp(cnpj);
    int DV[2] = {0};

    // Calculo do primeiro digito.
    tmp.pop_back();
    tmp.pop_back();
    auto itC = tmp.rbegin();
    int mul = 2;
    QVector<int> soma;
    for(; itC != tmp.rend(); ++itC) {
        QChar c = *itC;
        if(c.isDigit()) {
            int d = c.digitValue();
            int res = d * mul++;
            soma.push_front(res);
        }else
            return false;
        if(mul > 9)
            mul = 2;
    }
    int somatoria = 0;
    for(auto i : soma) somatoria += i;
    int m = somatoria % 11;
    int r = (m < 2 ? 0 : (11 - m));
    DV[1] = r;
    tmp = tmp.append(QString("%1").formatArg(DV[1]));

    // Calculo do segundo digito.
    itC = tmp.rbegin();
    mul = 2;
    soma.clear();
    for(; itC != tmp.rend(); ++itC) {
        QChar c = *itC;
        if(c.isDigit()) {
            int d = c.digitValue();
            int res = d * mul++;
            soma.push_front(res);
        }else
            return false;
        if(mul > 9)
            mul = 2;
    }
    somatoria = 0;
    for(auto i : soma) somatoria += i;
    m = somatoria % 11;
    r = (m < 2 ? 0 : (11 - m));
    DV[0] = r;
    tmp = tmp.append(QString("%1").formatArg(DV[0]));

    if(cnpj == tmp)
        return true;

    return false;
}