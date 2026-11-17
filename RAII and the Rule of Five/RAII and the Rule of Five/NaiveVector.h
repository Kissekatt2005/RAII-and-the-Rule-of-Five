#pragma once
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>


namespace workshop {
	class NaiveVector
	{
	public:
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

		std::size_t size() const noexcept { return size_; };
		bool empty() const noexcept { return size_ == 0; };
		const int* data() const noexcept { return data_; };
		int* data()  noexcept { return data_; };
		void swap(NaiveVector& other)
		{
			std::swap(data_, other.data_);
			std::swap(size_, other.size_);
		}

		int& at(std::size_t index)
		{
			if (index >= size_)
			{
				throw std::out_of_range("out of range");
			}
			return data_[index];
		}
		const int& at(std::size_t index) const
		{
			if (index >= size_)
			{
				throw std::out_of_range("out of range");
			}
			return data_[index];
		}
	private:
		std::size_t	size_ = 0;
		int* data_ = nullptr;
	};


}