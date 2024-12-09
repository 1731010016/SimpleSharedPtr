

struct ControlBlock {
	int ref_count;
	ControlBlock() : ref_count(1) {};
};


template<typename T>
class SimpleSharedPtr {
private:
	T* ptr;
	ControlBlock* control;
	viod release() {
		control->ref_count--;
		if (control->ref_count == 0) {
			delete ptr;
			ptr = nullptr;
			delete control;
			control = nullptr;
		}
	}
public:
	SimpleSharedPtr() :ptr(nullptr), control(nullptr) {};
	explicit SimpleSharedPtr(T* t) :ptr(t) {
		if (t) {
			control = new ControlBlock();
		}
		else
		{	
			control=nullptr
		}
	}
	~SimpleSharedPtr() {
		if (ptr){
			release();
		}
	}
};