#ifndef IREPOSITORY_H
#define IREPOSITORY_H

namespace service {


template <typename T> class IRepository {
public:
	IRepository() = default;
	virtual void reset() & = 0;
	virtual ~IRepository() { }
};


}  // service

#endif  // IREPOSITORY_H
