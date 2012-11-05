#include <finc/fincfield.h>

FinCField* finc_field_new (String* p_name, FinCType* p_type)
{
    FinCField *self;
    
    self = (FinCField*)mem_new(sizeof(FinCField));
    object_init_object (OBJECT (self), finc_field_destroy);
    
    self->type = addref (FinCType, p_type);
    self->name = addref (String, p_name);
    
    self->offset = 0;
    self->index = 0;
    
    return self;
}

void finc_field_destroy (Object* self)
{
    unref (FinC_FIELD (self)->type);
    unref (FinC_FIELD (self)->name);
    
    mem_destroy (self);
}
