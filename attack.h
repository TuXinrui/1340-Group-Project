// attack_detection.h 
#include <string>
using namespace std;

//���������󣬴������ĵ�ͼ�����λ��
void attack_detect(string target, string** ptr, string** ptr_seen, int x, int y, int damage);
//�ѱ��ϴ����߽������µ���ͼ��
void broken_update(string target, string item, string** ptr);
//���Ŀ����ҵĴ����߽����Ƿ񱨷�
void broken_detect(string target, string item, string** ptr);
//ʹ�ù�������
void attack_input_conversion(string target, string** ptr, string** ptr_seen, string command, int x, int y, int damage);
//���⼼��
void skills(string target, string** ptr, string** ptr_seen, string command, int x1, int y1, int x2, int y2);

