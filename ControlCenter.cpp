#include "ControlCenter.h"
#define once_step 30

ControlCenter::ControlCenter(list<EVETank> Other)
{
	NumberDead = 0;
	auto it = Other.begin();
	while (it != Other.end())
	{
		EVETank* temp = new EVETank(*it);
		int *co = new int(rand() % once_step + 1);
		int* dir = new int(rand() % 4);
		OtherTank.push_back(temp);
		count.push_back(co);
		direction.push_back(dir);
		++it;
	}
}


void ControlCenter::RuningTime()
{
	for (list<int *>::iterator it_count = count.begin(), it_dir = direction.begin(); it_count != count.end(); ++it_count,++it_dir)
	{
		if (**it_count <= 0)
		{
			**it_count= rand() % once_step + 1;
			**it_dir = rand() % 4;
		}
	}
	list<EVETank*>::iterator it_tank = OtherTank.begin();
	for (list<int*>::iterator it_dir = direction.begin(); it_tank != OtherTank.end(); ++it_tank, ++it_dir)
	{
		switch (**it_dir)
		{
		case 0:
			(*it_tank)->move(UP);
			break;
		case 1:
			(*it_tank)->move(RIGHT);
			break;
		case 2:
			(*it_tank)->move(DOWN);
			break;
		case 3:
			(*it_tank)->move(LEFT);
			break;
		default:
			break;
		}
	}
	for (auto it_count = count.begin(); it_count != count.end(); ++it_count)
		--(**it_count);
}


void ControlCenter::DisplayAuto(DWORD defa)
{
	putimage(graph_x1, graph_y1, &BGImage1, defa);
	auto it_friend = FriendTank.begin();
	while (it_friend != FriendTank.end())
	{
		(*it_friend)->display();
		++it_friend;
	}
	list<EVETank*>::iterator it_tank = OtherTank.begin();
	while (it_tank != OtherTank.end())
	{
		(*it_tank)->display();
		++it_tank;
	}
	list<Bullet_Biu *>::iterator it_bullet = AllBullet.begin();
	while (it_bullet != AllBullet.end())
	{
		(*it_bullet)->display();
		++it_bullet;
	}
}

void ControlCenter::FireBullet(TankType &Tank)
{
	Bullet_Biu* bullet;
	bullet = new Bullet_Biu(Tank.GetGunPosx(), Tank.GetGunPosy(), Tank.GetDirection(),Tank.harmH);
	AllBullet.push_back(bullet);
}

void ControlCenter::UserAttack()
{
	auto it_friend = FriendTank.begin();
	while (it_friend != FriendTank.end())
	{
		if ((*it_friend)->GetID() == 1)
			FireBullet(**it_friend);
		else
			break;
		++it_friend;
	}
}

void ControlCenter::BulletRun()
{
	auto it_bullet = AllBullet.begin();
	while (it_bullet != AllBullet.end())
	{
		(*it_bullet)->move();
		if ((*it_bullet)->GetPosX() == graph_x1 || (*it_bullet)->GetPosX() == graph_x2 || (*it_bullet)->GetPosY() == graph_y1 || (*it_bullet)->GetPosY() == graph_y2 || KillTank(*it_bullet))
		{
			Bullet_Biu* temp = *it_bullet;
			it_bullet = AllBullet.erase(it_bullet);
			delete temp;
			continue;
		}
		++it_bullet;
	}
}
/*
bool Jingzhundaji(int edge,int dir,int x,int y,int bullet_x,int bullet_y)
{
	switch (dir)
	{
	case (0):
		if (bullet_x >= x && bullet_x <= x + edge)
			if (bullet_y >= y && bullet_y <= y + 2 * edge)
				return true;
		return false;
	case (1):
		if (bullet_x >= x-edge && bullet_x <= x + edge)
			if (bullet_y >= y && bullet_y <= y + edge)
				return true;
		return false;
	case (2):
		if (bullet_x >= x && bullet_x <= x + edge)
			if (bullet_y >= y-edge && bullet_y <= y + edge)
				return true;
		return false;
	case (3):
		if (bullet_x >= x && bullet_x <= x + edge*2)
			if (bullet_y >= y && bullet_y <= y + edge)
				return true;
		return false;
	default:
		return false;
	}
}*/


bool ControlCenter::KillTank(Bullet_Biu* bullet)
{
	auto it_tank = OtherTank.begin();
	auto it_count = count.begin();
	auto it_dir = direction.begin();
	while (it_tank != OtherTank.end())
	{
		if (bullet->GetPosX() >= (*it_tank)->GetPosX() && bullet->GetPosX() <= (*it_tank)->GetPosX() + (*it_tank)->GetSqure())
		{
			if (bullet->GetPosY() >= (*it_tank)->GetPosY() && bullet->GetPosY() <= (*it_tank)->GetPosY() + (*it_tank)->GetSqure())
			{
				if ((*it_tank)->HP <= bullet->GetHurtHP())
				{
					EVETank* temp1 = (*it_tank);
					int* temp2 = *it_count;
					int* temp3 = *it_dir;
					it_tank = OtherTank.erase(it_tank);
					it_count = count.erase(it_count);
					it_dir = direction.erase(it_dir);
					delete temp1;
					delete temp2;
					delete temp3;
					++NumberDead;
				}
				else
					((*it_tank)->HP) -= (bullet->GetHurtHP());
				return true;
			}
		}
		++it_dir;
		++it_count;
		++it_tank;
	}
	auto it_user = FriendTank.begin();
	while (it_user != FriendTank.end())
	{
		if (bullet->GetPosX() >= (*it_user)->GetPosX() && bullet->GetPosX() <= (*it_user)->GetPosX() + (*it_user)->GetSqure())
		{
			if (bullet->GetPosY() >= (*it_user)->GetPosY() && bullet->GetPosY() <= (*it_user)->GetPosY() + (*it_user)->GetSqure())
			{
				if ((*it_user)->HP <= bullet->GetHurtHP())
				{
					TankType* temp = (*it_user);
					it_user = FriendTank.erase(it_user);
					delete temp;
				}
				else
					((*it_user)->HP) -= (bullet->GetHurtHP());
				return true;
			}
		}
		
		++it_user;
	}
	return false;
}


void ControlCenter::AutoAttack()
{
	auto it_friend = FriendTank.begin();
	while (it_friend != FriendTank.end())
	{
		TankType Tank = **it_friend;
		auto it_tank = OtherTank.begin();
		auto it_count = count.begin();
		while (it_tank != OtherTank.end())
		{
			switch ((*it_tank)->GetDirection())
			{
			case 0:
				if ((*it_tank)->GetGunPosx() >= Tank.GetPosX() && (*it_tank)->GetGunPosx() <= Tank.GetPosX() + Tank.GetSqure() && (*it_tank)->GetGunPosy() > Tank.GetPosY())
				{
					FireBullet(**it_tank);
					++(**it_count);
				}
				break;
			case 1:
				if ((*it_tank)->GetGunPosy() >= Tank.GetPosY() && (*it_tank)->GetGunPosy() <= Tank.GetPosY() + Tank.GetSqure() && (*it_tank)->GetGunPosx() < Tank.GetPosX())
				{
					FireBullet(**it_tank);
					++(**it_count);
				}
				break;
			case 2:
				if ((*it_tank)->GetGunPosx() >= Tank.GetPosX() && (*it_tank)->GetGunPosx() <= Tank.GetPosX() + Tank.GetSqure() && (*it_tank)->GetGunPosy() < Tank.GetPosY())
				{
					FireBullet(**it_tank);
					++(**it_count);
				}
				break;
			case 3:
				if ((*it_tank)->GetGunPosy() >= Tank.GetPosY() && (*it_tank)->GetGunPosy() <= Tank.GetPosY() + Tank.GetSqure() && (*it_tank)->GetGunPosx() > Tank.GetPosX())
				{
					FireBullet(**it_tank);
					++(**it_count);
				}
				break;
			default:
				break;
			}
			++it_tank;
			++it_count;
		}
		++it_friend;
	}
}

void ControlCenter::AddEveTank(int num)
{
	EVETank* p;
	int* temp;
	int* dir;
	for (int i = 0; i < num; ++i)
	{
		p = new EVETank(rand() % (graph_x2 - SQUREEDGE - graph_x1 - 2 * GUNLEN) + graph_x1 + GUNLEN, rand() % (graph_y2 - SQUREEDGE - graph_y1 - 2 * GUNLEN) + graph_y1 + GUNLEN, RGB(rand() % 256, rand() % 256, rand() % 256));
		temp = new int(rand() % once_step + 1);
		dir = new int(rand() % 4);
		OtherTank.push_back(p);
		count.push_back(temp);
		direction.push_back(dir);
	}
}

void ControlCenter::AddFriendTank(int num)
{
	TankType* p;
	for (int i = 0; i < num; ++i)
	{
		p = new TankType();
		FriendTank.push_back(p);
	}
}

void ControlCenter::AddUserTank()
{
	MyTank* p;
	p = new MyTank();
	FriendTank.push_back(p);
}

void ControlCenter::UserMove(char ch)
{
	auto it_friend = FriendTank.begin();
	while (it_friend != FriendTank.end())
	{
		if ((*it_friend)->GetID() == 1)
			(*it_friend)->move(ch);
		else
			break;
		++it_friend;
	}
}

bool ControlCenter::Is_UserEmpty() const
{
	if (FriendTank.empty())
		return true;
	else
	{
		if ((FriendTank.front())->GetID() != 1)
			return true;
	}
	return false;
}


void ControlCenter::AddBossTank(int num)
{
	BossTank* p;
	int* temp;
	int* dir;
	for (int i = 0; i < num; ++i)
	{
		int t = rand() % 2;
		p = new BossTank( t*760+70, 120, RGB(rand() % 256, rand() % 256, rand() % 256), RGB(rand() % 256, rand() % 256, rand() % 256));
		temp = new int(rand() % once_step + 1);
		dir = new int(rand() % 4);
		OtherTank.push_back(p);
		count.push_back(temp);
		direction.push_back(dir);
	}
}

void ControlCenter::FireDirBullet(TankType& Aim,TankType& mine)
{
	DirBullet* bullet = new DirBullet(mine.GetGunPosx(),mine.GetGunPosy(),Aim.GetPosX(),Aim.GetPosY());
	AllBullet.push_back(bullet);
}

void ControlCenter::AimAttack()
{
	auto it_tank = OtherTank.begin();
	while (it_tank != OtherTank.end())
	{
		if ((*it_tank)->GetID() == 3)
		{
			auto it_friend = FriendTank.end();
			if (it_friend != FriendTank.begin())
			{
				--it_friend;
				FireDirBullet(**it_friend, **it_tank);
			}
		}
		++it_tank;
	}
}


void ControlCenter::AimMove()
{
	auto it_tank = OtherTank.begin();
	while (it_tank != OtherTank.end())
	{
		//if ((*it_tank)->GetID() == 3)
		//{
			auto id_friend = FriendTank.end();
			if (id_friend != FriendTank.begin())
			{
				--id_friend;
				(*it_tank)->move(**id_friend);
			}
		//
		++it_tank;
	}
}

void ControlCenter::KillAllEVE()
{
	auto it_tank = OtherTank.begin();
	auto it_count = count.begin();
	auto it_dir = direction.begin();
	while (it_tank != OtherTank.end())
	{
		EVETank* temp1 = (*it_tank);
		int* temp2 = *it_count;
		int* temp3 = *it_dir;
		it_tank = OtherTank.erase(it_tank);
		it_count = count.erase(it_count);
		it_dir = direction.erase(it_dir);
		delete temp1;
		delete temp2;
		delete temp3;
		++NumberDead;
	}
}

bool ControlCenter::Is_BossEmpty()
{
	auto it_tank = OtherTank.begin();
	while (it_tank != OtherTank.end())
	{
		if ((*it_tank)->GetID() == 3)
			return false;
		++it_tank;
	}
	return true;
}

void ControlCenter::AppearProps()
{
	px = rand() % (graph_x2 - SQUREEDGE - graph_x1 - 2 * GUNLEN) + graph_x1 + GUNLEN;
	py = rand() % (graph_y2 - SQUREEDGE - graph_y1 - 2 * GUNLEN) + graph_y1 + GUNLEN;
}
void ControlCenter::DrawProps()
{
	if (px == 0 || py == 0)
		return;
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 28;						// 设置字体高度为 48
	_tcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);
	char s[] = "?";
	outtextxy(px, py, s);
}

bool ControlCenter::Is_GetProps()//加速，加伤害，加血
{
	if (px == 0 || py == 0)
	{
		if (Increation.empty())
			return false;
		else
			return true;
	}
	int temp = 0;
	auto it_friend = FriendTank.begin();
	while (it_friend != FriendTank.end())
	{
		if ((*it_friend)->GetID() == 1)
		{
			if ((*it_friend)->GetPosX() < px && (*it_friend)->GetPosX() + (*it_friend)->GetSqure() > px)
				if ((*it_friend)->GetPosY() < py && (*it_friend)->GetPosY() + (*it_friend)->GetSqure() > py)
				{
					temp = (rand() % 3) + 1;
					px = 0;
					py = 0;
					break;
				}
		}
		++it_friend;
	}
	if (temp == 1)
	{
		Increation.push_back(1);
		((*it_friend)->move_speed) += Increation_speed;
	}
	else if (temp == 2)
	{
		Increation.push_back(2);
		((*it_friend)->harmH) += Increation_HurtHP;
	}
	else if (temp == 3)
	{
		Increation.push_back(3);
		((*it_friend)->HP) += Increation_HP;
	}
	if (Increation.empty())
		return false;
	else
		return true;
}

void ControlCenter::RecoveryNormal()
{
	auto it_friend = FriendTank.begin();
	while (it_friend != FriendTank.end())
	{
		if ((*it_friend)->GetID() == 1)
		{
			if (Increation.empty())
				return;
			else
			{
				auto it = Increation.begin();
				while (it != Increation.end())
				{
					if (*it==1)
						((*it_friend)->move_speed) -= Increation_speed;
					else if (*it == 2)
						((*it_friend)->harmH) -= Increation_HurtHP;
					it = Increation.erase(it);
				}
			}
		}
		++it_friend;
	}
}

int ControlCenter::GetCurrHP()
{
	auto it_friend = FriendTank.begin();
	while (it_friend != FriendTank.end())
	{
		if ((*it_friend)->GetID() == 1)
		{
			int temp = (*it_friend)->HP;
			return temp * 20;
		}
		++it_friend;
	}
	return 0;
}