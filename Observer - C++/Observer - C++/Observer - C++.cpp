#include <iostream>
#include <string>
#include <vector>
using namespace std;

__interface IObserver {
	virtual void Update(double p) = 0;
};

class IObservable {
public:
	virtual void AddObserver(IObserver* o) = 0;
	virtual void RemoveObserve(IObserver* o) = 0;

	virtual void Notify() = 0;
	virtual ~IObservable(){}
};

class Product : public IObservable {
private:
	vector <IObserver*> observer;
	double price;
public:
	Product(double p) : price(p){}
	void ChangePrice(double p) {
		price = p;
		Notify();
	}
	void AddObserver(IObserver* o) override {
		observer.push_back(o);
	}
	void RemoveObserve(IObserver* o) override {
		observer.erase(remove(observer.begin(), observer.end(), o), observer.end());
	}
	void Notify() override {
		for (auto o : observer) {
			o->Update(price);
		}
	}
};

class Wholesaler : public IObserver {
private:
	IObservable* product;
public:
	Wholesaler(IObservable* obj) : product(obj) {
		obj->AddObserver(this);
	}
	void Update(double p) override {
		if (p < 300) {
			cout << "the wholesaler purchased the goods at a price: " << p << "\n";
			product->RemoveObserve(this);
		}
	}
};

class Buyer : public IObserver {
private:
	IObservable* product;
public:
	Buyer(IObservable* obj) : product(obj) {
		obj->AddObserver(this);
	}
	void Update(double p) override {
		if (p < 350) {
			cout << "The buyer purchased the goods at a price: " << p << "\n";
			product->RemoveObserve(this);
		}
	}
};

int main(){
	Product* product = new Product(400);
	Wholesaler* wholesaler = new Wholesaler(product);
	Buyer* buyer = new Buyer(product);
	product->ChangePrice(320);
	product->ChangePrice(280);
}