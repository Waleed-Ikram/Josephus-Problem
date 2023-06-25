#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

template <class T>
class Node
{
public : 
	T data;
	Node<T>* next;

	Node()
	{
		next = NULL;
	}
};

template <class T>
class Circular_Queue
{
public : 
	Node<T>* front;
	Node<T>* rear;

	Circular_Queue()
	{
		front = rear = NULL;
	}

	void Enqueue(T element)
	{
		Node<T>* temp = new Node<T>;

		temp->data = element;

		if (front == NULL)
		{
			front = temp;  // case queue is empty 
		}
		else
		{
			rear->next = temp;  // appended at the end of the queue
		}

		rear = temp;
		rear->next = front;  // to make circular queue
	}

	T Dequeue()
	{
		if (front == NULL)
			return 0;

		Node<T>* temp = front;
		T element;

		if (front == rear)  // case only one element 
		{
			//temp = front; 
			element = temp->data;
			front = NULL;
			rear = NULL;
		}
		else
		{
			//temp = front;
			element = front->data;
			front = front->next;
			rear->next = front;
		}

		delete temp;
		return element;
	}

	bool is_last()
	{
		return (front == rear);
	}

	void skip()
	{
		if (front == NULL)
			return;

		front = front->next;
		rear = rear->next;
	}

	void print()
	{
		Node<T>* temp = front;
		cout << "\nYour QUEUE : \n";
		while (temp->next != front)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}

		cout << temp->data;
	}
};

int execute(Circular_Queue<int>& queue, int k)
{
	int data = 0;
	
	if (!queue.is_last())
	{
		for (int i = 0; i < k; i++)
		{
			queue.skip();
		}

		data = queue.Dequeue();
	}

	return data;
}

int main()
{
	int N = 0;
	int K;
	int data = 0;
	while (N < 1) 
	{
		cout << "How many men are there ?" << endl;
		cin >> N;
	
	}
	cout << "\nWhat is the order of execution ?\n";
	cin >> K;

	Circular_Queue<int> queue;

	for (int i = 1; i <= N; i++)   //This loop populates a queue with numbers uptill N
	{
		queue.Enqueue(i);
	}

	queue.print();

	sf::RenderWindow window(sf::VideoMode(1900, 1050), "JOSEPHUS PROBLEM", sf::Style::Close | sf::Style::Resize);
	sf::RectangleShape soldier(sf::Vector2f(150.0f, 200.0f));
	sf::RectangleShape killed_soldier(sf::Vector2f(150.0f, 200.0f));
	killed_soldier.setFillColor(sf::Color::Red);
	

	sf::Texture soldier_texture;
	soldier_texture.loadFromFile("texture.jpg");
	soldier.setTexture(&soldier_texture);
	killed_soldier.setTexture(&soldier_texture);

	int* arr = new int[N];
	for (int i = 0; i < N; i++)
	{
		arr[i] = 0;
	}

	while (window.isOpen())
	{
		sf::Event evnt;
		
		while (window.pollEvent(evnt))
		{
			if (evnt.type == evnt.Closed)
				window.close();

		}

		int x = 10;
		int y = 10;

		for (int i = 0; i < N; i++)
		{
			if (x > 1820)
			{
				x = 10;
				y = y + 230;
			}

			if (arr[i] == 1)
			{
				killed_soldier.setPosition(x, y);
				window.draw(killed_soldier);
			}
			else
			{
				soldier.setPosition(x, y);
				window.draw(soldier);
			}
			x = x + 170;

			window.display();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			data = execute(queue, K);
			data = data - 1;
			arr[data] = 1;
		}
		
	}
	

}