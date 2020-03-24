#pragma once
#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "ArraryList.h"
#include "FolderType.h"
#include "Queue.h"
#include "ItemType.h"
#include "DoublyLinkedList.h"

class Application
{
private:
	FolderType m_RootFolder;		///< item list.criptor.
	FolderType* m_curFolder;		///< item list.
	FolderType m_iterator;
	ItemType* m_curItem;
	int m_Command;			///< current command number.
	Queue<FolderType*> m_RecentlyFolder;
public:
	Application()
	{
		m_Command = 0;

		m_RootFolder.SetName("root");
		m_RootFolder.SetPath("/root");
		m_RootFolder.SetCreatTime(m_RootFolder.GetCurTime());
		m_RootFolder.GetSubFolderNum();
		m_curFolder = &m_RootFolder;
		// m_curFile = &m_

	}

	~Application() {}
	/**
	*	@brief	���α׷� driver.
	*	@pre	���α׷��� ���۵�.
	*	@post	���α׷��� �����.
	*/
	void Run();

	/**
	*	@brief	��ɾ ȭ�鿡 ����ϰ� ��ɾ Ű����κ��� �Է¹޴´�.
	*	@pre	����.
	*	@post	����.
	*	@return	������� ��ɾ� return.
	*/
	int GetCommand();

	/** @1: �� ���� ����
	*	@brief	���ο� ������ list�� �߰�.
	*	@pre	list�� �ʱ�ȭ�Ǿ�� �Ѵ�.
	*	@post	���ο� ������ list�� �߰���.
	*	@return	�Լ��� �� �۵��ϸ� 1�� return, �׷��������� 0�� return
	*/
	int NewFolder();

	/** @2: �̸����� ���� �˻�
	*	@brief	����ڷκ��� �Է¹��� �̸����� ������ �˻���
	*	@pre	iterator�� ����Ʈ �� ó������ ����.
	*	@post	iterator�� ����Ʈ �� �� �������� �̵�.
	*	@return	�Լ��� �� �۵��ϸ� 1�� return, �׷��������� �޼��� ��°� �Բ� 0�� return
	*/
	int RetrieveFolderByName();

	/** @3: ���� ����
	*	@brief	�����̸��� ������ �Է¹޾� ����Ʈ���� ����
	*	@pre	list�� �ʱ�ȭ�Ǿ�� �Ѵ�.
	*	@post	������� �ϴ� ������ list���� ������.
	*/
	int DeleteFolder();

	/** @4: ���� ����
	*	@brief	�����̸��� �Է¹޾� ���������� �˻�
	*	@pre	list�� �ʱ�ȭ�Ǿ�� �Ѵ� & Queue �غ�
	*	@post	�˻��ϰ����ϴ� ���������� list���� ��µ� & Queue�� ���
	*/
	void OpenFolder();

	/** @5: ���� �̸� �����ϱ�
	*	@brief �Էµ� ������ ����Ʈ���� ���������� ã�� �̸�����
	*	@pre	id�� �Է¹���
	*	@post	�����ϰ� ���� ������ ����
	*	@return	����
	*/

	void ReplaceFolder();

	/** @6 : ���� ���� �Ӽ�
 :	*	@brief	���� �̸��� �Է¹޾� ����Ʈ���� ã�Ƽ� �Ӽ� ���
	*	@pre	list�� �ʱ�ȭ�Ǿ�� �Ѵ�.
	*	@post	ǥ���ϰ� ���� �����Ӽ��� ȭ�鿡 ��µ�.
	*/
	void DisplayProperty();

	/** @7 : �ֱ� �� ���� ���
	*	@brief	�ֱ� ��� ��������� ȭ�鿡 ǥ��
	*	@pre	Queue�ȿ� �ֱٿ� ��� ���� �̸��� �Էµ�
	*	@post	�ֱ� ��� ���� ��ϵ��� ȭ�鿡 ��µ�.
	*/
	void RecentlyFolder();

	/** @8 : ���� ������ �̵�
	*	@brief	���������� �̵��ϴ� �Լ�
	*	@pre	�̵��� �������� Stack�� ���δ�
	*	@post	���������� �̵��Ѵ�.
	*/
	void MoveBack();

	/** @9 : ���� ������ �̵�
	*	@brief	���������� �̵��ϴ� �Լ�
	*	@pre	���������� ������
	*	@post	���������� �̵��Ѵ�.
	*/
	void MoveTo();

	/** @10 : ���ο� �ڷ� ����
	*	@brief	���ο� �ڷḦ Itemlist�� �߰�.
	*	@pre	list�� �ʱ�ȭ�Ǿ�� �Ѵ�.
	*	@post	���ο� ������ list�� �߰���.
	*	@return	�Լ��� �� �۵��ϸ� 1�� return, �׷��������� 0�� return
	*/
	int NewItem();

	/** @11: �̸����� �ڷ� �˻�
	*	@brief	����ڷκ��� �Է¹��� �̸����� �ڷḦ �˻���
	*	@pre	iterator�� ����Ʈ �� ó������ ����.
	*	@post	iterator�� ����Ʈ �� �� �������� �̵�.
	*	@return	�Լ��� �� �۵��ϸ� 1�� return, �׷��������� �޼��� ��°� �Բ� 0�� return
	*/
	int RetrieveItemByName();

	/** @12 : �ڷ� ����
	*	@brief	�����̸��� ������ �Է¹޾� ���ϸ���Ʈ���� ����
	*	@pre	list�� �ʱ�ȭ�Ǿ�� �Ѵ�.
	*	@post	������� �ϴ� ���� list���� ������.
	*/
	int DeleteItem();

	/** @13 : �ڷ� ����
	*	@brief	�����̸��� ������ �Է¹޾� ������ ����
	*	@pre	list�� �ʱ�ȭ�Ǿ�� �Ѵ�.
	*	@post	���ϳ����� ȭ�鿡 ��µ�.
	*/
	void OpenItem();

	/** @14 : �ڷ� �̸� ����
	*	@brief �Էµ� ������ ����Ʈ���� ���������� ã�� ����
	*	@pre	id�� �Է¹���
	*	@post	�����ϰ� ���� ������ ����
	*	@return	����
	*/
	void ReplaceItem();
};
#endif // !_APPLICATION_H
