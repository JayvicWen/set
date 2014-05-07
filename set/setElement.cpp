#include "stdafx.h"

#include <algorithm>
#include <iterator>

#include "setElement.h"

CSetElement::CSetElement() : mark(ELE_SET)
{
}

CSetElement::CSetElement(const MarkType &tMark) : mark(tMark)
{
}

CSetElement::CSetElement(const CString &tString) : mark(ELE_STRING), dataString(tString)
{
}

CSetElement::CSetElement(const MyPair &tPair) : mark(ELE_PAIR), dataPair(tPair)
{
}

CSetElement::CSetElement(const MySet &tSet) : mark(ELE_SET), dataSet(tSet)
{
}

CSetElement::CSetElement(const CSetElement &tEle)
    : mark(tEle.mark), dataString(tEle.dataString), 
    dataSet(tEle.dataSet), dataPair(tEle.dataPair)
{
}

CSetElement::~CSetElement()
{
}

CSetElement & CSetElement::operator=(const CSetElement &tEle)
{
    mark = tEle.mark;
    dataString = tEle.dataString;
    dataSet = tEle.dataSet;
    dataPair = tEle.dataPair;
    return *this;
}

bool operator==(const CSetElement &eleA, const CSetElement &eleB)
{
    if (eleA.mark != eleB.mark)
    {
        return false;
    }
    if (eleA.mark == ELE_STRING)
    {
        return eleA.dataString == eleB.dataString;
    }
    if (eleA.mark == ELE_PAIR)
    {
        return eleA.dataPair == eleB.dataPair;
    }
    //eleA.mark == ELE_SET
    return eleA.dataSet == eleB.dataSet;
}

bool operator!=(const CSetElement &eleA, const CSetElement &eleB)
{
    return !(eleA == eleB);
}

bool operator<(const CSetElement &eleA, const CSetElement &eleB)
{
    if (eleA.mark != eleB.mark)
    {
        return eleA.mark < eleB.mark;
    }
    if (eleA.mark == ELE_STRING)
    {
        return (eleA.dataString.GetLength() == eleB.dataString.GetLength()) ? 
            eleA.dataString < eleB.dataString : eleA.dataString.GetLength() < eleB.dataString.GetLength();
    }
    if (eleA.mark == ELE_PAIR)
    {
        return eleA.dataPair < eleB.dataPair;
    }
    //eleA.mark == ELE_SET
    return (eleA.dataSet.size() == eleB.dataSet.size()) ? 
        eleA.dataSet < eleB.dataSet : eleA.dataSet.size() < eleB.dataSet.size();
}

bool operator>(const CSetElement &eleA, const CSetElement &eleB)
{
    return !(eleA < eleB);
}

MarkType CSetElement::GetMark(void) const
{
    return mark;
}

CString CSetElement::GetEleString(void) const
{
    return dataString;
}

MyPair CSetElement::GetElePair(void) const
{
    return dataPair;
}

MySet CSetElement::GetEleSet(void) const
{
    return dataSet;
}

void CSetElement::SetMark(const MarkType &tMark)
{
    mark = tMark;
}

void CSetElement::SetEleString(const CString &tString)
{
    dataString = tString;
}

void CSetElement::SetElePair(const MyPair &tPair)
{
    dataPair = tPair;
}

void CSetElement::SetEleSet(const MySet &tSet)
{
    dataSet = tSet;
}

//�ж��Ƿ�Ϊ����
bool CSetElement::IsSet(void) const
{
    return mark == ELE_SET;
}

//�ж��Ƿ�Ϊ��Ԫ��ϵ
bool CSetElement::IsRelation(void) const
{
    if (mark != ELE_SET)
    {
        return false;
    }
    for (SetIter iter = dataSet.begin(); iter != dataSet.end(); iter++)
    {
        if (iter->mark != ELE_PAIR)
        {
            return false;
        }
    }
    return true;
}

//�ж��Ƿ�Ϊ�Է���ϵ
bool CSetElement::IsReflexiveRelation(const MySet &rangeSet) const
{
    if (!IsRelation())
    {
        return false;
    }
    for (SetIter iter = rangeSet.begin(); iter != rangeSet.end(); iter++)
    {
        MyPair tPair;
        tPair.push_back(*iter);
        tPair.push_back(*iter);
        if (dataSet.find(CSetElement(tPair)) == dataSet.end())
        {
            return false;
        }
    }
    return true;
}

//�ж��Ƿ�Ϊ�Գƹ�ϵ
bool CSetElement::IsSymmetricRelation(void) const
{
    if (!IsRelation())
    {
        return false;
    }
    for (SetIter iter = dataSet.begin(); iter != dataSet.end(); iter++)
    {
        if (dataSet.find(iter->GetOppositePair()) == dataSet.end())
        {
            return false;
        }
    }
    return true;
}

//�ж��Ƿ�Ϊ���ݹ�ϵ
bool CSetElement::IsTransitiveRelation(void) const
{
    if (!IsRelation())
    {
        return false;
    }
    for (SetIter iterA = dataSet.begin(); iterA != dataSet.end(); iterA++)
    {
        for (SetIter iterB = dataSet.begin(); iterB != dataSet.end(); iterB++)
        {
            if (iterA->dataPair[1] == iterB->dataPair[0])
            {
                MyPair tPair;
                tPair.push_back(iterA->dataPair[0]);
                tPair.push_back(iterB->dataPair[1]);
                if (dataSet.find(CSetElement(tPair)) == dataSet.end())
                {
                    return false;
                }
            }
        }
    }
    return true;
}

//�ж��Ƿ�Ϊ�ȼ۹�ϵ
bool CSetElement::IsEquivalenceRelation(const MySet &rangeSet) const
{
    return IsReflexiveRelation(rangeSet) && IsSymmetricRelation() && IsTransitiveRelation();
}

//����������ԣ�������<x,y>������<y,x>
CSetElement CSetElement::GetOppositePair(void) const
{
    MyPair tPair;
    if (mark != ELE_PAIR)
    {
        return *this;
    }
    tPair.push_back(dataPair[1]);
    tPair.push_back(dataPair[0]);
    return CSetElement(tPair);
}

//���ϲ�
bool CSetElement::SetUnion(const CSetElement &eleA, const CSetElement &eleB)
{
    if (!eleA.IsSet() || !eleB.IsSet())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;
    set_union(eleA.dataSet.begin(), eleA.dataSet.end(), 
        eleB.dataSet.begin(), eleB.dataSet.end(), 
        inserter(dataSet, dataSet.begin()));
    return true;
}

//���Ͻ�
bool CSetElement::SetIntersection(const CSetElement &eleA, const CSetElement &eleB)
{
    if (!eleA.IsSet() || !eleB.IsSet())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;
    set_intersection(eleA.dataSet.begin(), eleA.dataSet.end(), 
        eleB.dataSet.begin(), eleB.dataSet.end(), 
        inserter(dataSet, dataSet.begin()));
    return true;
}

//������Բ�
bool CSetElement::SetDifference(const CSetElement &eleA, const CSetElement &eleB)
{
    if (!eleA.IsSet() || !eleB.IsSet())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;
    set_difference(eleA.dataSet.begin(), eleA.dataSet.end(), 
        eleB.dataSet.begin(), eleB.dataSet.end(), 
        inserter(dataSet, dataSet.begin()));
    return true;
}

//���϶ԳƲ�
bool CSetElement::SetSymmetricDifference(const CSetElement &eleA, const CSetElement &eleB)
{
    if (!eleA.IsSet() || !eleB.IsSet())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;
    set_symmetric_difference(eleA.dataSet.begin(), eleA.dataSet.end(), 
        eleB.dataSet.begin(), eleB.dataSet.end(), 
        inserter(dataSet, dataSet.begin()));
    return true;
}

//�ѿ�����
bool CSetElement::SetDescartes(const CSetElement &eleA, const CSetElement &eleB)
{
    if (!eleA.IsSet() || !eleB.IsSet())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    for (SetIter iterA = eleA.dataSet.begin(); iterA != eleA.dataSet.end(); iterA++)
    {
        for (SetIter iterB = eleB.dataSet.begin(); iterB != eleB.dataSet.end(); iterB++)
        {
            MyPair tPair;
            tPair.push_back(*iterA);
            tPair.push_back(*iterB);
            dataSet.insert(CSetElement(tPair));
        }
    }
    return true;
}

//��Ԫ��ϵ�Ҹ���
bool CSetElement::SetCompound(const CSetElement &eleA, const CSetElement &eleB)
{
    if (!eleA.IsRelation() || !eleB.IsRelation())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    for (SetIter iterA = eleA.dataSet.begin(); iterA != eleA.dataSet.end(); iterA++)
    {
        for (SetIter iterB = eleB.dataSet.begin(); iterB != eleB.dataSet.end(); iterB++)
        {
            if (iterA->dataPair[1] == iterB->dataPair[0])
            {
                MyPair tPair;
                tPair.push_back(iterA->dataPair[0]);
                tPair.push_back(iterB->dataPair[1]);
                dataSet.insert(CSetElement(tPair));
            }
        }
    }
    return true;
}

//�̼�
bool CSetElement::SetQuotient(const CSetElement &eleA, const CSetElement &eleB)
{
    if (!eleA.IsSet() || !eleB.IsEquivalenceRelation(eleA.dataSet))
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    vector<MySet> quot;
    for (SetIter iter = eleA.dataSet.begin(); iter != eleA.dataSet.end(); iter++)
    {
        vector<MySet>::iterator qIter;
        for (qIter = quot.begin(); qIter != quot.end(); qIter++)
        {
            MyPair tPair;
            tPair.push_back(*iter);
            tPair.push_back(*(qIter->begin()));
            if (eleB.dataSet.find(CSetElement(tPair)) != eleB.dataSet.end())
            {
                qIter->insert(*iter);
                break;
            }
        }
        if (qIter == quot.end())
        {
            MySet tSet;
            tSet.insert(*iter);
            quot.push_back(tSet);
        }
    }

    for (vector<MySet>::iterator qIter = quot.begin(); qIter != quot.end(); qIter++)
    {
        dataSet.insert(CSetElement(*qIter));
    }
    return true;
}

//��ϵ�ڼ����ϵ�����
bool CSetElement::SetLimit(const CSetElement &eleA, const CSetElement &eleB)
{
    if (!eleA.IsRelation() || !eleB.IsSet())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    for (SetIter iter = eleA.dataSet.begin(); iter != eleA.dataSet.end(); iter++)
    {
        if (eleB.dataSet.find(iter->dataPair[0]) != eleB.dataSet.end())
        {
            dataSet.insert(*iter);
        }
    }
    return true;
}

//�ݹ����������Ӽ�
void CSetElement::SubSetDfs(MySet &subSet, SetIter &iter, const SetIter &endIter)
{
    if (iter == endIter)
    {
        dataSet.insert(CSetElement(subSet));
        return;
    }
    SubSetDfs(subSet, ++iter, endIter);
    subSet.insert(*(--iter));
    SubSetDfs(subSet, ++iter, endIter);
    subSet.erase(*(--iter));
}

//�ݼ�
bool CSetElement::SetPowerSet(const CSetElement &eleA)
{
    if (!eleA.IsSet())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    SetIter iter = eleA.dataSet.begin();
    MySet subSet;
    SubSetDfs(subSet, iter, eleA.dataSet.end());
    return true;
}

//�Է��հ�
bool CSetElement::SetReflexiveClosure(const CSetElement &eleA, const CSetElement &eleB)
{
    if (!eleA.IsRelation() || !eleB.IsSet())
    {
        return false;
    }
    *this = eleA;

    for (SetIter iter = eleB.dataSet.begin(); iter != eleB.dataSet.end(); iter++)
    {
        MyPair tPair;
        tPair.push_back(*iter);
        tPair.push_back(*iter);
        dataSet.insert(CSetElement(tPair));
    }
    return true;
}

//�ԳƱհ�
bool CSetElement::SetSymmetricClosure(const CSetElement &eleA)
{
    if (!eleA.IsRelation())
    {
        return false;
    }
    *this = eleA;

    for (SetIter iter = eleA.dataSet.begin(); iter != eleA.dataSet.end(); iter++)
    {
        dataSet.insert(iter->GetOppositePair());
    }
    return true;
}

//���ݱհ�
bool CSetElement::SetTransitiveClosure(const CSetElement &eleA)
{
    if (!eleA.IsRelation())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    //��˹�ϵ����
    CSetElement fldSet(ELE_SET);
    fldSet.SetField(eleA);
    int n = fldSet.dataSet.size();

    //�Զ�������Ԫ�ر��
    vector<CSetElement> tzb(n);
    SetIter iter = fldSet.dataSet.begin();
    for (int i = 0; i < n; i++)
    {
        tzb[i] = *(iter++);
    }

    //��ʼ���ڽӾ���
    vector<vector<bool>> edge(n);
    MyPair tPair;
    tPair.resize(2);
    for (int i = 0; i < n; i++)
    {
        edge[i].resize(n);
        tPair[0] = tzb[i];
        for (int j = 0; j < n; j++)
        {
            tPair[1] = tzb[j];
            edge[i][j] = eleA.dataSet.find(CSetElement(tPair)) != eleA.dataSet.end();
        }
    }

    //Warshall�㷨
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                edge[i][j] = edge[i][j] | (edge[i][k] & edge[k][j]);
            }
        }
    }

    //����{R^i|i=1..oo}���뵽�����
    for (int i = 0; i < n; i++)
    {
        tPair[0] = tzb[i];
        for (int j = 0; j < n; j++)
        {
            if (edge[i][j])
            {
                tPair[1] = tzb[j];
                dataSet.insert(CSetElement(tPair));
            }
        }
    }

    return true;
}

//���ϵĶ�����
bool CSetElement::SetDomain(const CSetElement &eleA)
{
    if (!eleA.IsRelation())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    for (SetIter iter = eleA.dataSet.begin(); iter != eleA.dataSet.end(); iter++)
    {
        dataSet.insert(iter->dataPair[0]);
    }
    return true;
}

//���ϵ�ֵ��
bool CSetElement::SetRange(const CSetElement &eleA)
{
    if (!eleA.IsRelation())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    for (SetIter iter = eleA.dataSet.begin(); iter != eleA.dataSet.end(); iter++)
    {
        dataSet.insert(iter->dataPair[1]);
    }
    return true;
}

//���ϵ���
bool CSetElement::SetField(const CSetElement &eleA)
{
    if (!eleA.IsRelation())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    CSetElement eleB(ELE_SET), eleC(ELE_SET);
    eleB.SetDomain(eleA);
    eleC.SetRange(eleA);
    SetUnion(eleB, eleC);
    return true;
}

//��ϵ����
bool CSetElement::SetReverse(const CSetElement &eleA)
{
    if (!eleA.IsRelation())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    for (SetIter iter = eleA.dataSet.begin(); iter != eleA.dataSet.end(); iter++)
    {
        dataSet.insert(iter->GetOppositePair());
    }
    return true;
}

//��ϵ��n���ݣ������ݣ�
bool CSetElement::SetQuickPower(CSetElement eleA, int n)
{
    if (!eleA.IsRelation())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    CSetElement tEle(ELE_SET);
    tEle.SetField(eleA);
    for (SetIter iter = tEle.dataSet.begin(); iter != tEle.dataSet.end(); iter++)
    {
        MyPair tPair;
        tPair.push_back(*iter);
        tPair.push_back(*iter);
        dataSet.insert(CSetElement(tPair));
    }

    while (n > 0)
    {
        if ((n & 1) == 1)
        {
            tEle = *this;
            SetCompound(tEle, eleA);
        }
        tEle = eleA;
        eleA.SetCompound(tEle, tEle);
        n >>= 1;
    }

    return true;
}

//�ݹ���������A��B�ĺ���
void CSetElement::SetMappingDfs(MySet &subMapping, SetIter &iter, const SetIter &endIter, const CSetElement &eleB)
{
    if (iter == endIter)
    {
        dataSet.insert(CSetElement(subMapping));
        return;
    }
    MyPair tPair(2);
    tPair[0] = *(iter++);
    for (SetIter iterB = eleB.dataSet.begin(); iterB != eleB.dataSet.end(); iterB++)
    {
        tPair[1] = *iterB;
        subMapping.insert(CSetElement(tPair));
        SetMappingDfs(subMapping, iter, endIter, eleB);
        subMapping.erase(CSetElement(tPair));
    }
    iter--;
}

//��B��A
bool CSetElement::SetMapping(const CSetElement &eleA, const CSetElement &eleB)
{
    if (!eleA.IsSet() || !eleB.IsSet())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    SetIter iter = eleA.dataSet.begin();
    MySet subMapping;
    SetMappingDfs(subMapping, iter, eleA.dataSet.end(), eleB);
    return true;
}

//�ȼ���
bool CSetElement::SetEquivalenceClass(const CSetElement &eleA, const CSetElement &eleB, const MySet &rangeSet)
{
    if (!eleB.IsEquivalenceRelation(rangeSet))
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    for (SetIter iter = eleB.dataSet.begin(); iter != eleB.dataSet.end(); iter++)
    {
        if (iter->dataPair[0] == eleA)
        {
            dataSet.insert(iter->dataPair[1]);
        }
    }
    return true;
}

//���岢
bool CSetElement::SetGenUnion(const CSetElement &eleA)
{
    if (!eleA.IsSet())
    {
        return false;
    }
    dataSet.clear();
    mark = ELE_SET;

    for (SetIter iter = eleA.dataSet.begin(); iter != eleA.dataSet.end(); iter++)
    {
        CSetElement eleB(*this);
        if (!SetUnion(*iter, eleB))
        {
            return false;
        }
    }
    return true;
}

//���彻
bool CSetElement::SetGenIntersection(const CSetElement &eleA)
{
    if (!eleA.IsSet() || eleA.dataSet.empty() || !eleA.dataSet.begin()->IsSet())
    {
        return false;
    }
    *this = *(eleA.dataSet.begin());

    for (SetIter iter = eleA.dataSet.begin(); iter != eleA.dataSet.end(); iter++)
    {
        CSetElement eleB(*this);
        if (!SetIntersection(*iter, eleB))
        {
            return false;
        }
    }
    return true;
}