#include <cassert>
#include <algorithm>

#include "shared_ptr.hpp"

shared_ptr::Storage::Storage(Matrix* mtx)
{
  assert(mtx != nullptr);
  data_ = mtx;
  ref_count_ = 1;
}

shared_ptr::Storage::~Storage()
{
  assert(ref_count_ == 0);
  delete data_;
}

void shared_ptr::Storage::incr()
{
  assert(ref_count_ != 0);
  ref_count_++;
}

void shared_ptr::Storage::decr()
{
   assert(ref_count_ > 0);
   ref_count_--;
}

int shared_ptr::Storage::getCounter() const
{
  return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const
{
  return data_;
}

shared_ptr::shared_ptr(Matrix* obj) : storage_(nullptr)
{
  if (obj != nullptr)
    storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other)
{
  storage_ = other.storage_;
  incrPtr();
}

shared_ptr& shared_ptr::operator=(shared_ptr other)
{
  std::swap(storage_, other.storage_);

  return *this;
}

shared_ptr::~shared_ptr()
{
  decrPtr();
}

Matrix* shared_ptr::ptr() const
{
  if (!isNull())
    return storage_->getObject();
  return nullptr;
}

bool shared_ptr::isNull() const
{
  return storage_ == nullptr;
}

void shared_ptr::reset(Matrix* obj)
{
  decrPtr();

  if (obj != nullptr)
    storage_ = new Storage(obj);
  else
    storage_ = nullptr;
}

Matrix* shared_ptr::operator->() const
{
  assert(!isNull());
  return storage_->getObject();
}

Matrix& shared_ptr::operator*() const
{
  assert(!isNull());
  return *(storage_->getObject());
}

void shared_ptr::decrPtr()
{
  if (!isNull())
  { 
    storage_->decr();
    if (storage_->getCounter() == 0)
    {
      delete storage_;
      storage_ = nullptr;
    }
  }
}

void shared_ptr::incrPtr()
{
  if (!isNull())
    storage_->incr();
}