#pragma once

#include <set>
#include <vector>
//#include <utility>

using namespace std;

enum MarkType
{
    ELE_STRING, ELE_PAIR, ELE_SET
};

class CSetElement;

typedef set<CSetElement> MySet;
typedef set<CSetElement>::iterator SetIter;
//typedef pair<CSetElement, CSetElement> MyPair;
typedef vector<CSetElement> MyPair;

//����Ԫ���࣬����Ԫ�ؿ�Ϊ��ͨԪ�ء�����ԡ�����
//���еļ��ϣ���������һ������Ϊ���ϵļ���Ԫ�ش���
class CSetElement
{
public:
    CSetElement();
    CSetElement(const MarkType &tMark);
    CSetElement(const CSetElement &tEle);
    CSetElement(const CString &tString);
    CSetElement(const MyPair &tPair);
    CSetElement(const MySet &tSet);
    ~CSetElement();

    CSetElement & operator=(const CSetElement &tEle);

    friend bool operator==(const CSetElement &eleA, const CSetElement &eleB);
    friend bool operator!=(const CSetElement &eleA, const CSetElement &eleB);
    friend bool operator<(const CSetElement &eleA, const CSetElement &eleB);
    friend bool operator>(const CSetElement &eleA, const CSetElement &eleB);

    MarkType GetMark(void) const;
    CString GetEleString(void) const;
    MyPair GetElePair(void) const;
    MySet GetEleSet(void) const;
    void SetMark(const MarkType &tMark);
    void SetEleString(const CString &tString);
    void SetElePair(const MyPair &tPair);
    void SetEleSet(const MySet &tSet);

    bool IsSet(void) const;//�ж��Ƿ�Ϊ����
    bool IsRelation(void) const;//�ж��Ƿ�Ϊ��Ԫ��ϵ
    bool IsReflexiveRelation(const MySet &rangeSet) const;//�ж��Ƿ�Ϊ�Է���ϵ
    bool IsSymmetricRelation(void) const;//�ж��Ƿ�Ϊ�Գƹ�ϵ
    bool IsTransitiveRelation(void) const;//�ж��Ƿ�Ϊ���ݹ�ϵ
    bool IsEquivalenceRelation(const MySet &rangeSet) const;//�ж��Ƿ�Ϊ�ȼ۹�ϵ

    CSetElement GetOppositePair(void) const;//����������ԣ�������<x,y>������<y,x>

    bool SetUnion(const CSetElement &eleA, const CSetElement &eleB);//���ϲ�
    bool SetIntersection(const CSetElement &eleA, const CSetElement &eleB);//���Ͻ�
    bool SetDifference(const CSetElement &eleA, const CSetElement &eleB);//������Բ�
    bool SetSymmetricDifference(const CSetElement &eleA, const CSetElement &eleB);//���϶ԳƲ�
    bool SetDescartes(const CSetElement &eleA, const CSetElement &eleB);//�ѿ�����
    bool SetCompound(const CSetElement &eleA, const CSetElement &eleB);//��Ԫ��ϵ�Ҹ���
    bool SetQuotient(const CSetElement &eleA, const CSetElement &eleB);//�̼�
    bool SetLimit(const CSetElement &eleA, const CSetElement &eleB);//��ϵ�ڼ����ϵ�����
    bool SetPowerSet(const CSetElement &eleA);//�ݼ�
    bool SetReflexiveClosure(const CSetElement &eleA, const CSetElement &eleB);//�Է��հ�
    bool SetSymmetricClosure(const CSetElement &eleA);//�ԳƱհ�
    bool SetTransitiveClosure(const CSetElement &eleA);//���ݱհ�
    bool SetDomain(const CSetElement &eleA);//���ϵĶ�����
    bool SetRange(const CSetElement &eleA);//���ϵ�ֵ��
    bool SetField(const CSetElement &eleA);//���ϵ���
    bool SetReverse(const CSetElement &eleA);//��ϵ����
    bool SetQuickPower(CSetElement eleA, int n);//��ϵ��n���ݣ������ݣ�
    bool SetMapping(const CSetElement &eleA, const CSetElement &eleB);//��B��A
    bool SetEquivalenceClass(const CSetElement &eleA, const CSetElement &eleB, const MySet &rangeSet);//�ȼ���
    bool SetGenUnion(const CSetElement &eleA);//���岢
    bool SetGenIntersection(const CSetElement &eleB);//���彻

private:
    MarkType mark;
    CString dataString;
    MyPair dataPair;
    MySet dataSet;

    void SubSetDfs(MySet &subSet, SetIter &iter, const SetIter &endIter);//�ݹ����������Ӽ�
    void SetMappingDfs(MySet &subMapping, SetIter &iter, const SetIter &endIter, const CSetElement &eleB);//�ݹ���������A��B�ĺ���
};
