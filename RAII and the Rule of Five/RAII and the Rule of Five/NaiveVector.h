#pragma once
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <cassert>
#include <numeric>
#include <random> // default_random_engine

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
		explicit NaiveVector(std::size_t count, int value = 0) :size_{ count }, data_{ count > 0 ? new int[count] : nullptr } {
			if (data_ != nullptr)
			{
				std::fill_n(data_, size_, value);
			}
		}
		~NaiveVector() {
			delete[]data_;
		}

		NaiveVector(const NaiveVector& other) : size_{ other.size() }, data_{ nullptr }
		{
			if (!empty()) {
				data_ = new int[size()];
				std::copy_n(other.data(), size_, data());
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
			moved.swap(*this);
			return *this;
		}

		reference operator[](std::size_t index) noexcept
		{
			assert(index < size_);
			return data_[index];
		}

		const_reference operator[](std::size_t index) const noexcept
		{
			assert(index < size_);
			return data_[index];
		}

		reference front() noexcept {
			assert(!empty());
			return data_[0];
		}
		const_reference front() const noexcept {
			assert(!empty());
			return data_[0];
		}

		reference back() noexcept {
			assert(!empty());
			return data_[size() - 1];
		}
		const_reference back() const noexcept {
			assert(!empty());
			return data_[size() - 1];
		}

		std::size_t size() const noexcept { return size_; };
		bool empty() const noexcept { return size_ == 0; };
		const int* data() const noexcept { return data_; };
		int* data()  noexcept { return data_; };
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
			return data_[index];
		}
		const_reference at(std::size_t index) const
		{
			if (index >= size_)
			{
				throw std::out_of_range("out of range");
			}
			return data_[index];
		}
	private:
		size_type	size_ = 0;
		int* data_ = nullptr;
	};


}