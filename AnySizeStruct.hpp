// AnySizeStruct --- any-size-struct template
// This file is public domain software (PDS).
//////////////////////////////////////////////////////////////////////////////

#ifndef ANYSIZESTRUCT_HPP_
#define ANYSIZESTRUCT_HPP_

//////////////////////////////////////////////////////////////////////////////

#ifndef ANYSIZESTRUCT_CXX11
    #if (__cplusplus >= 201103L)
        // C++11
        #define ANYSIZESTRUCT_CXX11
    #endif
#endif

//////////////////////////////////////////////////////////////////////////////

#include <cstddef>                  // for size_t
#include <memory>                   // for std::allocator

#ifdef ANYSIZESTRUCT_CXX11
    #include <initializer_list>     // for std::initializer_list
#endif

//////////////////////////////////////////////////////////////////////////////

template <typename T_STRUCT, size_t t_size = sizeof(T_STRUCT)>
struct AnySizeStruct {
    char data[t_size];

    T_STRUCT *get() {
        return reinterpret_cast<T_STRUCT *>(data);
    }

    const T_STRUCT *get() const {
        return reinterpret_cast<const T_STRUCT *>(data);
    }

          T_STRUCT& ref()       { return *get(); }
    const T_STRUCT& ref() const { return *get(); }

public:
    // default constructor
    AnySizeStruct() {
        std::allocator<T_STRUCT> a;
        new(get()) T_STRUCT();
    }

    // copy constructor
    AnySizeStruct(const T_STRUCT& data) {
        std::allocator<T_STRUCT> a;
        a.construct(get(), data);
    }

    // copy constructor 2
    template <size_t t_size_2>
    AnySizeStruct(const AnySizeStruct<T_STRUCT, t_size_2>& ass) {
        std::allocator<T_STRUCT> a;
        a.construct(get(), *ass.get());
    }

    // assignment
    AnySizeStruct<T_STRUCT,t_size>& operator=(const T_STRUCT& data) {
        *get() = data;
        return *this;
    }

    // assignment 2
    template <size_t t_size_2>
    AnySizeStruct<T_STRUCT,t_size>&
    operator=(const AnySizeStruct<T_STRUCT, t_size_2>& ass) {
        *get() = *ass.get();
        return *this;
    }

    #ifdef ANYSIZESTRUCT_CXX11 // C++11
        // parameter pack constructor
        template <typename... T_ARGS>
        AnySizeStruct(T_ARGS... args) {
            std::allocator<T_STRUCT> a;
            a.construct(get(), args...);
        }

        // move constructor
        AnySizeStruct(T_STRUCT&& data) {
            std::allocator<T_STRUCT> a;
            a.construct(get(), std::move(data));
        }

        // move constructor 2
        template <size_t t_size_2>
        AnySizeStruct(AnySizeStruct<T_STRUCT, t_size_2>&& ass) {
            std::allocator<T_STRUCT> a;
            a.construct(get(), std::move(*ass.get()));
        }

        // move assignment
        AnySizeStruct<T_STRUCT,t_size>& operator=(T_STRUCT&& data) {
            *get() = std::move(data);
            return *this;
        }

        // move assignment 2
        template <size_t t_size_2>
        AnySizeStruct<T_STRUCT,t_size>&
        operator=(AnySizeStruct<T_STRUCT, t_size_2>&& ass) {
            *get() = std::move(*ass.get());
            return *this;
        }

        template <typename T_ELEMENT>
        AnySizeStruct(std::initializer_list<T_ELEMENT> elements) {
            std::allocator<T_STRUCT> a;
            a.construct(get(), elements);
        }
    #endif  // C++11

    // destructor
    ~AnySizeStruct() { get()->~T_STRUCT(); }

public:
    #ifdef ANYSIZESTRUCT_CXX11 // C++11
        constexpr
    #endif
    size_t size() const { return t_size; }

    #ifdef ANYSIZESTRUCT_CXX11 // C++11
        constexpr
    #endif
    size_t struct_size() const { return sizeof(T_STRUCT); }

          T_STRUCT *operator->()       { return get(); }
    const T_STRUCT *operator->() const { return get(); }

    #ifndef ANYSIZESTRUCT_STRICT
              T_STRUCT *operator&()       { return get(); }
        const T_STRUCT *operator&() const { return get(); }

        operator       T_STRUCT&()       { return *get(); }
        operator const T_STRUCT&() const { return *get(); }

              T_STRUCT& operator*()       { return *get(); }
        const T_STRUCT& operator*() const { return *get(); }
    #endif
}; // struct AnySizeStruct<T_STRUCT, t_size>

//////////////////////////////////////////////////////////////////////////////

#endif  // ndef ANYSIZESTRUCT_HPP_

//////////////////////////////////////////////////////////////////////////////
