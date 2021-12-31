template<class BaseT, int Size, bool copy=true, bool move=true>
    struct PolyObject {
        using Storage = std::aligned_storage<Size>::type;
        Storage storage;
        void * identity; //store Identity 
        
        template<class T>  
        PolyObject (T&& object){
            assign(std::forward<T>(object));
        }

        PolyObject(PolyObject&& other) noexcept // move constructor
        {
            assign(std::forward<T>(object));
        }

        PolyObject& operator=(const PolyObject& other) // copy assignment
        {
            return *this = rule_of_five(other);
        }

 
        struct ObjectHandler {
            


        }


    private:
        template<class T> 
        void assign (T&& object) {

            static_assert(sizeof(T) <= Size*4, "Debe ser menor al tamaño del objeto Poly");
            (*destructor)(storage);
            destructor = specific_destructor;
            new(static_cast<void*>(&storage)) T(object);
        }

        void do_nothing_destructor(Storage&) {};

        ~PolyObject() {
            (*destructor)(storage);
        }

    };