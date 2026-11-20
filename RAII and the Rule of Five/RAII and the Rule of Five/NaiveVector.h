#pragma once
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <cassert>
#include <iterator>
#include <numeric>
#include <random> // default_random_engine
#include <CodeAnalysis/Warnings.h>

namespace workshop {
	class NaiveVector
	{
	public:
		using value_type = int;
		using size_type = std::size_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = value_type*;
		using const_iterator = const value_type*;


		NaiveVector()  noexcept {};

#pragma warning(suppress : 26409)
		explicit NaiveVector(std::size_t count, int value = 0) :size_{ count }, data_{ count > 0 ? new int[count] : nullptr } {
			if (data_ != nullptr)
			{
			}
			std::fill_n(data_, size_, value);
		}
		~NaiveVector() {
#pragma warning(suppress : 26401 )
#pragma warning(suppress : 26409 )
			delete[] data_;
		}

		NaiveVector(const NaiveVector& other) : size_{ other.size() }, data_{ nullptr }
		{
			if (!empty()) {

#pragma warning(suppress : 26409)
				data_ = new int[size()];
#pragma warning(suppress : 26459)
				std::copy(other.begin(), other.end(), begin());
			}
		}
		NaiveVector& operator=(NaiveVector& other)
		{
			NaiveVector copy(other);
			copy.swap(*this);
			return *this;

		}
		NaiveVector(NaiveVector&& other) noexcept
		{
			data_ = other.data_;
			size_ = other.size_;
			other.data_ = nullptr;
			other.size_ = 0;
		}

		NaiveVector& operator=(NaiveVector&& other) noexcept
		{
			NaiveVector moved(std::move(other));
#pragma warning(suppress : 26447)
			moved.swap(*this);
			return *this;
		}

		reference operator[](std::size_t index) noexcept
		{
			assert(index < size_);
			//	return data_[index];

			return *std::next(data(), index);
		}

		const_reference operator[](std::size_t index) const noexcept
		{
			assert(index < size_);
#pragma warning(suppress : 26481)
			return data_[index];
		}

		reference front() noexcept {
			assert(!empty() && "hello");
			return data_[0];
		}
		const_reference front() const noexcept {
			assert(!empty());
			return data_[0];
		}

		reference back() noexcept {
			assert(!empty());
#pragma warning(suppress : 26481)
			return data_[size() - 1];
		}
		const_reference back() const noexcept {
			assert(!empty());
#pragma warning(suppress : 26481)
			return data_[size() - 1];
		}

		iterator begin() noexcept {
			return data();
		}

		const_iterator begin() const noexcept {
			return data();
		}

		iterator end() noexcept {
#pragma warning(suppress : 26481)
			return begin() + size();
		}

		const_iterator end() const noexcept {
#pragma warning(suppress : 26481)
			return begin() + size();
		}

		std::size_t size() const noexcept { return size_; };
		bool empty() const noexcept { return size_ == 0; };
		const int* data() const noexcept { return data_; };
		int* data()  noexcept { return data_; };
#pragma warning(suppress : 26440)
		void swap(NaiveVector& other)
		{
			std::swap(data_, other.data_);
			std::swap(size_, other.size_);
		}

		reference at(std::size_t index)
		{
			if (index >= size_)
			{
				throw std::out_of_range("out of range");
			}
#pragma warning(suppress : 26481)
			return data_[index];
		}
		const_reference at(std::size_t index) const
		{
			if (index >= size_)
			{
				throw std::out_of_range("out of range");
			}
#pragma warning(suppress : 26481)
			return data_[index];
		}
	private:
		size_type	size_ = 0;
		int* data_ = nullptr;
	};


}