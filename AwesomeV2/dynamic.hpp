#pragma once

/*#include <stdlib.h>
#include <vector>

template<class T>
class dynamic
{
private:
	T* m_data;

	using reference = T&;
	using const_reference = const T&;

public:
	dynamic() {
		m_data = (T*)malloc(sizeof(T));
	}

	dynamic(T* _data) {
		m_data = (T*)calloc(sizeof(_data) / sizeof(T), sizeof(T));

		m_data = _data;
	}

	dynamic(const std::vector<T> _data) {
		free(m_data);

		m_data = (T*)malloc(_data.size());

		m_data = _data.m_data();
	}

	void push_back(T value) {
		m_data = realloc(m_data, (sizeof(m_data) / sizeof(T)) + 1);

		m_data[sizeof(m_data) / sizeof(T)] = value;
	}

	void pop_back() {
		m_data = realloc(m_data, (sizeof(m_data) / sizeof(T)) - 1);
	}

	void resize(const uint32_t size) {
		m_data = realloc(m_data, (sizeof(m_data) / sizeof(T)) + size);
	}

	void clear() {
		free(m_data);

		m_data = (T*)malloc(sizeof(T));
	}

	void erase(const uint32_t size) {
		m_data = realloc(m_data, (sizeof(m_data) / sizeof(T)) - size);
	}

	void reserve(const uint32_t size) {
		m_data = (T*)calloc(sizeof(m_data) / sizeof(T) + size, sizeof(T));
	}

	void assign(const T* _data) {
		free(m_data);

		m_data = (T*)calloc(sizeof(_data) / sizeof(T), sizeof(T));

		m_data = _data;
	}

	void insert(const T* _data) {
		resize(sizeof(_data) / sizeof(T));

		for (uint32_t i = sizeof(m_data) / sizeof(T); i < (sizeof(m_data) / sizeof(T)) + (sizeof(_data) / sizeof(T)); i++)
		{
			m_data[i] = _data[i - (sizeof(m_data) / sizeof(T))];
		}
	}

	const T at(const uint32_t position) {
		return m_data[position];
	}

	uint32_t begin() {
		return 0;
	}

	uint32_t end() {
		return sizeof(m_data) / sizeof(T);
	}

	const uint32_t size() {
		return sizeof(m_data) / sizeof(T);
	}

	_CONSTEXPR20 bool empty() {
		return m_data == (T*)malloc(sizeof(T));
	}

	_NODISCARD _CONSTEXPR20 T* data() noexcept {
		return m_data;
	}

	_NODISCARD _CONSTEXPR20 T* data() const noexcept {
		return m_data;
	}

	reference operator[](uint32_t position) {
		return m_data[position];
	}

	//const_reference operator[](uint32_t position) {
	//	return m_data[position];
	//} const

	_CONSTEXPR20 dynamic& operator=(dynamic&& _data) noexcept {
		free(m_data);

		m_data = (T*)malloc(sizeof(_data) / sizeof(T));

		m_data = _data.data();

		return *this;
	}

	_CONSTEXPR20 dynamic& operator=(const dynamic& _data) {
		free(m_data);

		m_data = (T*)malloc(sizeof(_data) / sizeof(T));

		m_data = _data.data();
		
		return *this;
	}

	~dynamic() {
		free(m_data);
	}
};*/