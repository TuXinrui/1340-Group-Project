// attack_detection.h 
#ifndef ATTACK_H 
#define ATTACK_H
//�ѱ��ϴ����߽������µ���ͼ��
void broken_update(string target, string item, string** ptr);
//���Ŀ����ҵĴ����߽����Ƿ񱨷�
void broken_detect(string target, string item, string** ptr);
//���������󣬴������ĵ�ͼ�����λ��
void attack_detect(string target, string** ptr, int x, int y);
#endif 