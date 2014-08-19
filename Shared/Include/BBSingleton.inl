// Filename: BBSingleton.inl
// Author: Gael Huber

/**
* Instantiation for singleton instances
*/
template <typename Type>
Type* Singleton<Type>::_instance = 0;

/**
* Default constructor
*/
template <typename Type>
Singleton<Type>::Singleton()
{
	if(_instance == 0)
	{
		_instance = static_cast<Type*>(this);
	}

}

/**
* Destructor
*/
template <typename Type>
Singleton<Type>::~Singleton()
{
	if(_instance != 0)
	{
		delete _instance;
		_instance = 0;
	}
}

/**
* Copy constructor
* @param other The singleton instance to copy
*/
template <typename Type>
Singleton<Type>::Singleton(const Singleton& other)
{

}

/**
* Assignment operator
* @param other The singleton instance to assign
* @return The resultant singleton
*/
template <typename Type>
Singleton<Type>& Singleton<Type>::operator=(const Singleton& other)
{
	return *this;
}