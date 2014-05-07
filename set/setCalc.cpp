#include "stdafx.h"

#include <stack>

#include "setCalc.h"
#include "setElement.h"

static stack<CSetElement> eleStack;
static stack<TCHAR> opStack;
static vector<CSetElement> varSet(26, CSetElement(ELE_SET));

//�ж��Ƿ񲻿���Ϊһ�����ϵĿ�ʼ�ַ�
//inline static bool IsNotEleBegin(const TCHAR &c)
//{
//    return IsBinocularOperator(c) || (c == OP_RIGHT_BRACE) || (c == OP_RIGHT_PARENTHESIS)
//        || (c == OP_RIGHT_BRACKET);
//}

//�ж��Ƿ�������
inline static bool IsNumber(const TCHAR &c)
{
    return (c >= '0') && (c <= '9');
}

//�ж��Ƿ�Ϊ~A
inline static bool IsUnaryOperator1(const TCHAR &c)
{
    return c == OP_NEGATIVE;
}

//�ж��Ƿ�ΪP(A),r(R),s(R),t(R)
inline static bool IsUnaryOperator2(const TCHAR &c)
{
    return (c == OP_POWER_SET) || (c == OP_REFLEXIVE_CLOSURE) 
        || (c == OP_SYMMETRIC_CLOSURE) || (c == OP_TRANSITIVE_CLOSURE);
}

//�ж��Ƿ�ΪdomR,ranR,fldR
inline static bool IsUnaryOperator3(const CString &s)
{
    return (s == OP_DOMAIN) || (s == OP_RANGE) || (s == OP_FIELD);
}

//�ж��Ƿ�Ϊ˫Ŀ�����
inline static bool IsBinocularOperator(const TCHAR &c)
{
    return (c == OP_UNION) || (c == OP_INTERSECTION) || (c == OP_DIFFERENCE) 
        || (c == OP_SYMMETRIC_DIFFERENCE) || (c == OP_DESCARTES)
        || (c == OP_COMPOUND) || (c == OP_QUOTIENT) || (c == OP_LIMIT);
}

//�ж��Ƿ�Ϊ�����
inline static bool IsOperator(const TCHAR &c)
{
    for (int i = 0; i < OP_TABLE_LENGTH; i++)
    {
        if (c == OP_TABLE[i])
        {
            return true;
        }
    }
    return false;
}

//�ж��Ƿ�Ϊ���ϱ���
inline static bool IsVariable(const TCHAR &c)
{
    return (c >= TCHAR('A')) && (c <= TCHAR('Z'));
}

//�ж��Ƿ����Ϊһ�����ϵĽ����ַ�
inline static bool IsEleEnd(const TCHAR &c)
{
    return IsVariable(c) || IsNumber(c) || (c == OP_EMPTY_SET) || (c == OP_RIGHT_BRACE) 
        || (c == OP_RIGHT_PARENTHESIS) || (c == OP_RIGHT_BRACKET);
}

inline static int GetPriority(const TCHAR &c)
{
    //�ָ���
    if (c == OP_CUT_OFF)
    {
        return PRI_CUT_OFF;
    }
    //���ϲ�
    else if (c == OP_UNION)
    {
        return PRI_UNION;
    }
    //���Ͻ�
    else if (c == OP_INTERSECTION)
    {
        return PRI_INTERSECTION;
    }
    //������Բ�
    else if (c == OP_DIFFERENCE)
    {
        return PRI_DIFFERENCE;
    }
    //���϶ԳƲ�
    else if (c == OP_SYMMETRIC_DIFFERENCE)
    {
        return PRI_SYMMETRIC_DIFFERENCE;
    }
    //�ѿ�����
    else if (c == OP_DESCARTES)
    {
        return PRI_DESCARTES;
    }
    //��Ԫ��ϵ�Ҹ���
    else if (c == OP_COMPOUND)
    {
        return PRI_COMPOUND;
    }
    //�̼�
    else if (c == OP_QUOTIENT)
    {
        return PRI_QUOTIENT;
    }
    //��ϵ�ڼ����ϵ�����
    else if (c == OP_LIMIT)
    {
        return PRI_LIMIT;
    }
    //���ϵľ��Բ���
    else if (c == OP_NEGATIVE)
    {
        return PRI_NEGATIVE;
    }
    //�ݼ�
    else if (c == OP_POWER_SET)
    {
        return PRI_POWER_SET;
    }
    //�Է��հ�
    else if (c == OP_REFLEXIVE_CLOSURE)
    {
        return PRI_REFLEXIVE_CLOSURE;
    }
    //�ԳƱհ�
    else if (c == OP_SYMMETRIC_CLOSURE)
    {
        return PRI_SYMMETRIC_CLOSURE;
    }
    //���ݱհ�
    else if (c == OP_TRANSITIVE_CLOSURE)
    {
        return PRI_TRANSITIVE_CLOSURE;
    }
    //��ϵ�Ķ�����
    else if (c == OP_DOMAIN[2])
    {
        return PRI_DOMAIN;
    }
    //��ϵ��ֵ��
    else if (c == OP_RANGE[2])
    {
        return PRI_RANGE;
    }
    //��ϵ����
    else if (c == OP_FIELD[2])
    {
        return PRI_FIELD;
    }
    //�η�����
    else if (c == OP_POWER)
    {
        return PRI_POWER;
    }
    //R[A]
    else if (c == OP_LEFT_BRACKET)
    {
        return PRI_LEFT_BRACKET;
    }
    //[x]R
    else if (c == OP_RIGHT_BRACKET)
    {
        return PRI_RIGHT_BRACKET;
    }
    //���岢
    else if (c == OP_REG_GEN_UNION)
    {
        return PRI_GEN_UNION;
    }
    //���彻
    else if (c == OP_REG_GEN_INTERSECTION)
    {
        return PRI_GEN_INTERSECTION;
    }
    return -1;
}

inline static bool CmpPriority(const TCHAR &c1, const TCHAR &c2)
{
    return GetPriority(c1) <= GetPriority(c2);
}

//����ջ�����������һ������
static bool CalcOnce(void)
{
    if (eleStack.empty())
    {
        return false;
    }
    TCHAR op = opStack.top();
    opStack.pop();
    //���ϲ�
    if (op == OP_UNION)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetUnion(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //���Ͻ�
    else if (op == OP_INTERSECTION)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetIntersection(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //������Բ�
    else if (op == OP_DIFFERENCE)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetDifference(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //���϶ԳƲ�
    else if (op == OP_SYMMETRIC_DIFFERENCE)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetSymmetricDifference(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //�ѿ�����
    else if (op == OP_DESCARTES)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetDescartes(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //��Ԫ��ϵ�Ҹ���
    else if (op == OP_COMPOUND)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetCompound(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //�̼�
    else if (op == OP_QUOTIENT)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetQuotient(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //��ϵ�ڼ����ϵ�����
    else if (op == OP_LIMIT)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetLimit(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //B��A
    else if (op == OP_POWER)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetMapping(eleB, eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //����R[A]
    else if (op == OP_LEFT_BRACKET)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetLimit(eleA, eleB))
        {
            return false;
        }
        if (!eleB.SetRange(eleC))
        {
            return false;
        }
        eleStack.push(eleB);
    }
    //����[x]R
    else if (op == OP_RIGHT_BRACKET)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetEquivalenceClass(eleA, eleB, varSet[TCHAR('E') - TCHAR('A')].GetEleSet()))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //���ϵľ��Բ���
    else if (op == OP_NEGATIVE)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetDifference(varSet[TCHAR('E') - TCHAR('A')], eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //�ݼ�
    else if (op == OP_POWER_SET)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetPowerSet(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //�Է��հ�
    else if (op == OP_REFLEXIVE_CLOSURE)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetReflexiveClosure(eleA, varSet[0]))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //�ԳƱհ�
    else if (op == OP_SYMMETRIC_CLOSURE)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetSymmetricClosure(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //���ݱհ�
    else if (op == OP_TRANSITIVE_CLOSURE)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetTransitiveClosure(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //��ϵ�Ķ�����
    else if (op == OP_DOMAIN[2])
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetDomain(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //��ϵ��ֵ��
    else if (op == OP_RANGE[2])
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetRange(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //��ϵ����
    else if (op == OP_FIELD[2])
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetField(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //���岢
    else if (op == OP_REG_GEN_UNION)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetGenUnion(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //���彻
    else if (op == OP_REG_GEN_INTERSECTION)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetGenIntersection(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    return true;
}

//�жϱ��ʽ�����Ƿ�ƥ��
static bool IsBracketMatch(const CString &sInput)
{
    stack<TCHAR> bracketStack;
    bracketStack.push(OP_CUT_OFF);
    for (int i = 0; i < sInput.GetLength(); i++)
    {
        const TCHAR &c = sInput[i];
        if ((c == OP_LEFT_PARENTHESIS) || (c == OP_LEFT_BRACE)
            || (c == OP_LEFT_BRACKET) || (c == OP_LEFT_ANGLE_BKT))
        {
            bracketStack.push(c);
        }
        else if (c == OP_RIGHT_PARENTHESIS)
        {
            if (bracketStack.top() != OP_LEFT_PARENTHESIS)
            {
                return false;
            }
            bracketStack.pop();
        }
        else if (c == OP_RIGHT_BRACE)
        {
            if (bracketStack.top() != OP_LEFT_BRACE)
            {
                return false;
            }
            bracketStack.pop();
        }
        else if (c == OP_RIGHT_BRACKET)
        {
            if (bracketStack.top() != OP_LEFT_BRACKET)
            {
                return false;
            }
            bracketStack.pop();
        }
        else if (c == OP_RIGHT_ANGLE_BKT)
        {
            if (bracketStack.top() != OP_LEFT_ANGLE_BKT)
            {
                return false;
            }
            bracketStack.pop();
        }
    }
    return bracketStack.top() == OP_CUT_OFF;
}

//�������ջ��ͬʱ����ջ�����Լ�����������
static bool CalcAndPush(const TCHAR &c)
{
    while (CmpPriority(c, opStack.top()))
    {
        if (!CalcOnce())
        {
            return false;
        }
    }
    opStack.push(c);
    return true;
}

//������ʽ
static bool DealInput(const CString &sInput, int &pos)
{
    int inEleStackSize = eleStack.size();

    opStack.push(OP_CUT_OFF);
    while ((sInput[pos] != OP_COMMA) && (sInput[pos] != OP_RIGHT_BRACE) 
        && (sInput[pos] != OP_RIGHT_ANGLE_BKT) && (sInput[pos] != OP_RIGHT_PARENTHESIS)
        && (sInput[pos] != OP_CUT_OFF) && (sInput[pos] != OP_RIGHT_BRACKET))
    {
        //����Ϊ���ϵ����
        if (sInput[pos] == OP_LEFT_BRACE)
        {
            MySet inputSet;
            pos++;
            if (sInput[pos] != OP_RIGHT_BRACE)
            {
                while (true)
                {
                    if (!DealInput(sInput, pos))
                    {
                        return false;
                    }
                    inputSet.insert(eleStack.top());
                    eleStack.pop();

                    if (sInput[pos] == OP_RIGHT_BRACE)
                    {
                        break;
                    }
                    else if (sInput[pos] == OP_COMMA)
                    {
                        pos++;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            pos++;

            eleStack.push(CSetElement(inputSet));
        }
        //����Ϊ����Ե����
        else if (sInput[pos] == OP_LEFT_ANGLE_BKT)
        {
            MyPair inputPair;

            pos++;
            if (!DealInput(sInput, pos))
            {
                return false;
            }
            inputPair.push_back(eleStack.top());
            eleStack.pop();

            if (sInput[pos] != OP_COMMA)
            {
                return false;
            }
            pos++;
            if(!DealInput(sInput, pos))
            {
                return false;
            }
            inputPair.push_back(eleStack.top());
            eleStack.pop();

            if (sInput[pos] != OP_RIGHT_ANGLE_BKT)
            {
                return false;
            }
            pos++;

            eleStack.push(CSetElement(inputPair));
        }
        //����Ϊ(�����
        else if (sInput[pos] == OP_LEFT_PARENTHESIS)
        {
            pos++;
            if (!DealInput(sInput, pos))
            {
                return false;
            }
            if (sInput[pos] != OP_RIGHT_PARENTHESIS)
            {
                return false;
            }
            pos++;
        }
        //����Ϊ�ռ��������
        else if (sInput[pos] == OP_EMPTY_SET)
        {
            eleStack.push(CSetElement(ELE_SET));
            pos++;
        }
        //�����ϵ����
        else if ((sInput[pos] == OP_POWER) && (sInput[pos + 1] == TCHAR('-'))
            && (sInput[pos + 2] == TCHAR('1')))
        {
            CSetElement eleA = eleStack.top();
            eleStack.pop();
            CSetElement eleC;
            if (!eleC.SetReverse(eleA))
            {
                return false;
            }
            eleStack.push(eleC);
            pos += 3;
        }
        //�����ϵ��n����
        else if ((sInput[pos] == OP_POWER) && IsNumber(sInput[pos + 1]))
        {
            int n = 0;
            while (IsNumber(sInput[++pos]))
            {
                n = n * 10 + (int)(sInput[pos] - TCHAR('0'));
            }
            CSetElement eleA = eleStack.top();
            eleStack.pop();
            CSetElement eleC;
            if (!eleC.SetQuickPower(eleA, n))
            {
                return false;
            }
            eleStack.push(eleC);
        }
        //����ΪB��A�����
        else if (sInput[pos] == OP_POWER)
        {
            if ((sInput[pos + 1] != OP_UNION) && (sInput[pos + 1] != OP_INTERSECTION) 
                && IsBinocularOperator(sInput[pos + 1]))
            {
                return false;
            }
            opStack.push(sInput[pos++]);
        }
        //����R[A]��[x]R
        else if (sInput[pos] == OP_LEFT_BRACKET)
        {
            bool flag = (pos > 0) && IsEleEnd(sInput[pos - 1]);
            if (flag)
            {
                if (!CalcAndPush(sInput[pos]))
                {
                    return false;
                }
            }
            if (!DealInput(sInput, ++pos))
            {
                return false;
            }
            if (sInput[pos] != OP_RIGHT_BRACKET)
            {
                return false;
            }
            if (!flag)
            {
                if (!CalcAndPush(sInput[pos]))
                {
                    return false;
                }
            }
            pos++;
        }
        //����Ϊ���岢�����
        else if ((sInput[pos] == OP_UNION) && ((pos == 0) || !IsEleEnd(sInput[pos - 1])))
        {
            opStack.push(OP_REG_GEN_UNION);
            pos++;
        }
        //����Ϊ���彻�����
        else if ((sInput[pos] == OP_INTERSECTION) && ((pos == 0) || !IsEleEnd(sInput[pos - 1])))
        {
            opStack.push(OP_REG_GEN_INTERSECTION);
            pos++;
        }
        //����Ϊ˫Ŀ����������
        else if (IsBinocularOperator(sInput[pos]))
        {
            if ((sInput[pos + 1] != OP_UNION) && (sInput[pos + 1] != OP_INTERSECTION) 
                && IsBinocularOperator(sInput[pos + 1]))
            {
                return false;
            }
            if (!CalcAndPush(sInput[pos++]))
            {
                return false;
            }
        }
        //����Ϊ~�����
        else if (IsUnaryOperator1(sInput[pos]))
        {
            opStack.push(sInput[pos++]);
        }
        //����ΪP(A),r(R),s(R),t(R)�����
        else if (IsUnaryOperator2(sInput[pos]) && (sInput[pos + 1] == OP_LEFT_PARENTHESIS))
        {
            opStack.push(sInput[pos++]);
        }
        //����ΪdomR,ranR,fldR�����
        else if ((pos + 2 < sInput.GetLength()) && IsUnaryOperator3(sInput.Mid(pos, 3))
            && ((sInput[pos + 3] == OP_LEFT_PARENTHESIS) || (sInput[pos + 3] == OP_LEFT_BRACE)
            || (sInput[pos + 3] == OP_EMPTY_SET) || (IsVariable(sInput[pos + 3]) && IsOperator(sInput[pos + 4]))))
        {
            opStack.push(sInput[pos + 2]);
            pos += 3;
        }
        //����Ϊ���ϱ��������
        else if (IsVariable(sInput[pos]) && IsOperator(sInput[pos + 1]))
        {
            eleStack.push(varSet[sInput[pos++] - TCHAR('A')]);
        }
        //����Ϊ��ͨԪ�ص����
        else if (!IsOperator(sInput[pos]))
        {
            int i;
            for (i = pos + 1; !IsOperator(sInput[i]); i++)
            {
            }

            eleStack.push(CSetElement(sInput.Mid(pos, i - pos)));
            pos = i;
        }
        else
        {
            return false;
        }
    }

    while (opStack.top() != OP_CUT_OFF)
    {
        if (!CalcOnce())
        {
            return false;
        }
    }
    opStack.pop();

    return eleStack.size() == inEleStackSize + 1;
}

//������������ַ���sResult
static void OutputElement(const CSetElement &outEle, CString &sResult)
{
    if (outEle.GetMark() == ELE_STRING)
    {
        sResult += outEle.GetEleString();
    }
    else if (outEle.GetMark() == ELE_PAIR)
    {
        MyPair outPair = outEle.GetElePair();
        sResult += OP_LEFT_ANGLE_BKT;
        OutputElement(outPair[0], sResult);
        sResult += OP_COMMA;
        OutputElement(outPair[1], sResult);
        sResult += OP_RIGHT_ANGLE_BKT;
    }
    else //if (outEle.GetMark() == ELE_SET)
    {
        MySet outSet = outEle.GetEleSet();
        if (outSet.empty())
        {
            sResult += OP_EMPTY_SET;
        } 
        else
        {
            sResult += OP_LEFT_BRACE;
            for (SetIter iter = outSet.begin(); iter != outSet.end(); iter++)
            {
                if (iter != outSet.begin())
                {
                    sResult += OP_COMMA;
                }
                OutputElement(*iter, sResult);
            }
            sResult += OP_RIGHT_BRACE;
        }
    }
}

//���㼯�ϱ��ʽ����Ľӿ�
bool CalcExpression(CString sInput, CString &sResult, const TCHAR &cChoose)
{
    //��ʼ��ջ
    while (!eleStack.empty())
    {
        eleStack.pop();
    }
    while (!opStack.empty())
    {
        opStack.pop();
    }

    //������ʽ
    int pos = 0;
    sInput += OP_CUT_OFF;
    if (!IsBracketMatch(sInput) || !DealInput(sInput, pos) || (pos < sInput.GetLength() - 1))
    {
        return false;
    }

    varSet[cChoose - TCHAR('A')] = eleStack.top();

    //�����ת�����ַ���
    sResult = "";
    OutputElement(eleStack.top(), sResult);

    return true;
}
