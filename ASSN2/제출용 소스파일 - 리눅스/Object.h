#ifndef __OBJECT_H
#define __OBJECT_H

class Object
{
private:
	int axisX, axisY;	//object�� ��ġ ����
protected:
	//�̵� �޼ҵ�
	void moveUp();		//default game constructor
	void moveDown();	//custom game constructor
public:
	Object();
	Object(int a, int b);
	void moveLeft();
	void moveRight();
	int getAxisX() const;
	int getAxisY() const;
	void setAxisX(int const newAxisX);
	void setAxisY(int const newAxisY);
};
#endif // !__OBJECT_H




