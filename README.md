# Boost Serialization examples

In simple words, **serialization** consists of convert any data structure in a format that allows the data to be written on a support (file, socket etc.).

Boost offers a serialization library that comes with out-of-the-box serialization for POD and stl types but it is easy to use, especially with polymorphism. In this repository, I explore some different possible cases that I encounter commonly while programming.

## Serialize method

Each object that you are going to serialize requires that you implement the `serialize` method. It should take an archive as an argument (discussed later).

An archive is similar to an input/output data stream. Instead of using the operators `<<` or `>>` (that can be used too) you can use the general operator `&` to handle bot saving and loading operation. In other words, the following two examples are  

## Archive

To serialize the data, you can use different types of formats (e.g. text, binary etc.) for each format there will be a reading and writing operations defined. Boost library abstract the two operations for a given format with the concept of _archive_.

Boost offers several archives, i.e.

```c
// a portable text archive
boost::archive::text_oarchive // saving
boost::archive::text_iarchive // loading

// a portable text archive using a wide character stream
boost::archive::text_woarchive // saving
boost::archive::text_wiarchive // loading

// a portable XML archive
boost::archive::xml_oarchive // saving
boost::archive::xml_iarchive // loading

// a portable XML archive which uses wide characters (use for utf-8 output)
boost::archive::xml_woarchive // saving
boost::archive::xml_wiarchive // loading

// a non-portable native binary archive
boost::archive::binary_oarchive // saving
boost::archive::binary_iarchive // loading
```

### Make NVP

In this [simple](simple/main.cpp) subproject, I used text archive since they are portable and easy to use. A more interesting archive is the XML archive. Interfaces to all archive classes are all identical but XML archives present a somewhat special case. In fact, XML format requires a name for each data member, in a **name-value-pair** fashion. The Boost developer defined a helper function `make_nvp`, to facilitate it. The obvious way to use it is:

```c
ar & boost::serialization::make_nvp("member", member);
```

where the member key must be a valid XML attribute. To simplify typing and readability a macro is defined so we can write

```c
ar & BOOST_SERIALIZATION_NVP(member);
```

that expands exactly as the previous one.

It is safe to use `make_nvp` (or the associated macro) if you are using any other archive since it would expand to

```c
ar & member;
```

### Polymorphism

When Boost has to handle polymorphism we need to statically **register** each class. This helps Boost to correctly serialize the derived class at runtime. To register a class you have to use the `BOOST_CLASS_EXPORT` macro. It is important to place the macro in the same source module that includes any of the archive class headers.

Inherited members are serialized by accessing the `serialize()` method of the base class by calling `boost::serialization::base_object()`. It is placed inside the serialize method of the derived class.

```c
void serialize(Archive &ar, const unsigned int version) {
    ar & boost::serialization::base_object<Base>(*this);
}
```

To properly handle XML tags in the **name-value-pair**, we should call

```c
void serialize(Archive &ar, const unsigned int version) {
  ar & boost::serialization::make_nvp( "Base", boost::serialization::base_object<Base>(*this) )
}
```

similarly to `make_nvp`, Boost define a macro that expands as the above

```c
void serialize(Archive &ar, const unsigned int version) {
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Base)
}
```

## Usage

### Requirements

To compile this code you need:

- Boost library
- Catch (for unit tests)

### Compile and execute

To compile the code, run

```sh
mkdir build
cd build
cmake ..
make
```

This will produce three binaries, 

- `simple/serdes_simple`
- `simple/unittest_serdes`
- `polymorphism/serdes_polymorph`

## Reference

- [Boost Serialization tutorial](https://www.boost.org/doc/libs/1_67_0/libs/serialization/doc/tutorial.html)
- [Special Consideration](https://www.boost.org/doc/libs/1_67_0/libs/serialization/doc/special.html)
- [Serialization of class hierarchies](https://theboostcpplibraries.com/boost.serialization-class-hierarchies)