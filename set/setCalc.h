#pragma once

//������ű�
//���÷���: �w���㩤
const CString OP_TABLE = _T("${}<>,[]()�ȡ�|&��#-��*��.��/��@~^�š�?����������������������");
const int OP_TABLE_LENGTH = OP_TABLE.GetLength();
const TCHAR OP_CUT_OFF = OP_TABLE[0];//�ָ���
const TCHAR OP_LEFT_BRACE = OP_TABLE[1];//�������
const TCHAR OP_RIGHT_BRACE = OP_TABLE[2];//�Ҵ�����
const TCHAR OP_LEFT_ANGLE_BKT = OP_TABLE[3];//�������
const TCHAR OP_RIGHT_ANGLE_BKT = OP_TABLE[4];//�Ҽ�����
const TCHAR OP_COMMA = OP_TABLE[5];//����
const TCHAR OP_LEFT_BRACKET = OP_TABLE[6];//������
const TCHAR OP_RIGHT_BRACKET = OP_TABLE[7];//�ҷ�����
const TCHAR OP_LEFT_PARENTHESIS = OP_TABLE[8];//��С����
const TCHAR OP_RIGHT_PARENTHESIS = OP_TABLE[9];//��С����
const TCHAR OP_UNION = OP_TABLE[10];//���ϲ�
const TCHAR OP_INTERSECTION = OP_TABLE[11];//���Ͻ�
const TCHAR OP_INPUT_UNION = OP_TABLE[12];//���ϲ����������
const TCHAR OP_INPUT_INTERSECTION = OP_TABLE[13];//���Ͻ����������
const TCHAR OP_SYMMETRIC_DIFFERENCE = OP_TABLE[14];//���϶ԳƲ�
const TCHAR OP_INPUT_SYM_DIFFERENCE = OP_TABLE[15];//���϶ԳƲ���������
const TCHAR OP_DIFFERENCE = OP_TABLE[16];//������Բ�
const TCHAR OP_DESCARTES = OP_TABLE[17];//�ѿ�����
const TCHAR OP_INPUT_DESCARTES = OP_TABLE[18];//�ѿ��������������
const TCHAR OP_COMPOUND = OP_TABLE[19];//��Ԫ��ϵ�Ҹ���
const TCHAR OP_INPUT_COMPOUND = OP_TABLE[20];//��Ԫ��ϵ�Ҹ��ϵ��������
const TCHAR OP_EMPTY_SET = OP_TABLE[21];//�ռ�����
const TCHAR OP_QUOTIENT = OP_TABLE[22];//�̼�
const TCHAR OP_LIMIT = OP_TABLE[23];//��ϵ�ڼ����ϵ�����
const TCHAR OP_INPUT_LIMIT = OP_TABLE[24];//��ϵ�ڼ����ϵ����Ƶ��������
const TCHAR OP_NEGATIVE = OP_TABLE[25];//���ϵľ��Բ���
const TCHAR OP_POWER = OP_TABLE[26];//�η�����
const TCHAR OP_REG_GEN_UNION = OP_TABLE[27];//���岢���洢ʱʹ�ã��벢����
const TCHAR OP_REG_GEN_INTERSECTION = OP_TABLE[28];//���彻���洢ʱʹ�ã��뽻����
const TCHAR OP_INPUT_EMPTY_SET = OP_TABLE[29];//�ռ����ŵ��������
//const TCHAR OP_DIFFERENCE = OP_TABLE[30];//������Բ�
const TCHAR OP_FULL_LEFT_BRACE = OP_TABLE[30];//�������(ȫ��)
const TCHAR OP_FULL_RIGHT_BRACE = OP_TABLE[31];//�Ҵ�����(ȫ��)
const TCHAR OP_FULL_LEFT_ANGLE_BKT = OP_TABLE[32];//�������(ȫ��)
const TCHAR OP_FULL_RIGHT_ANGLE_BKT = OP_TABLE[33];//�Ҽ�����(ȫ��)
const TCHAR OP_FULL_COMMA = OP_TABLE[34];//����(ȫ��)
const TCHAR OP_FULL_LEFT_BRACKET = OP_TABLE[35];//������(ȫ��)
const TCHAR OP_FULL_RIGHT_BRACKET = OP_TABLE[36];//�ҷ�����(ȫ��)
const TCHAR OP_FULL_LEFT_PARENTHESIS = OP_TABLE[37];//��С����(ȫ��)
const TCHAR OP_FULL_RIGHT_PARENTHESIS = OP_TABLE[38];//��С����(ȫ��)
const TCHAR OP_FULL_COMPOUND = OP_TABLE[39];//��Ԫ��ϵ�Ҹ���(ȫ��)
const TCHAR OP_FULL_EMPTY_SET = OP_TABLE[40];//�ռ�����(ȫ��)

const TCHAR OP_POWER_SET = TCHAR('P');//�ݼ�
const TCHAR OP_REFLEXIVE_CLOSURE = TCHAR('r');//�Է��հ�
const TCHAR OP_SYMMETRIC_CLOSURE = TCHAR('s');//�ԳƱհ�
const TCHAR OP_TRANSITIVE_CLOSURE = TCHAR('t');//���ݱհ�

const CString OP_DOMAIN = _T("dom");//��ϵ�Ķ�����
const CString OP_RANGE = _T("ran");//��ϵ��ֵ��
const CString OP_FIELD = _T("fld");//��ϵ����

//������������ȼ�
const int PRI_CUT_OFF = 0;//�ָ���
const int PRI_UNION = 10;//���ϲ�
const int PRI_INTERSECTION = 10;//���Ͻ�
const int PRI_DIFFERENCE = 10;//������Բ�
const int PRI_SYMMETRIC_DIFFERENCE = 10;//���϶ԳƲ�
const int PRI_DESCARTES = 20;//�ѿ�����
const int PRI_COMPOUND = 30;//��Ԫ��ϵ�Ҹ���
const int PRI_QUOTIENT = 15;//�̼�
const int PRI_LIMIT = 15;//��ϵ�ڼ����ϵ�����
const int PRI_NEGATIVE = 50;//���ϵľ��Բ���
const int PRI_POWER_SET = 50;//�ݼ�
const int PRI_REFLEXIVE_CLOSURE = 50;//�Է��հ�
const int PRI_SYMMETRIC_CLOSURE = 50;//�ԳƱհ�
const int PRI_TRANSITIVE_CLOSURE = 50;//���ݱհ�
const int PRI_DOMAIN = 50;//��ϵ�Ķ�����
const int PRI_RANGE = 50;//��ϵ��ֵ��
const int PRI_FIELD = 50;//��ϵ����
const int PRI_POWER = 60;//�η�����
const int PRI_LEFT_BRACKET = 50;//R[A]
const int PRI_RIGHT_BRACKET = 50;//[x]R
const int PRI_GEN_UNION = 50;//���岢
const int PRI_GEN_INTERSECTION = 50;//���彻

bool CalcExpression(CString sInput, CString &sResult, const TCHAR &cChoose);