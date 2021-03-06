static VALUE arf_create_random_engine(VALUE self, VALUE type_val, VALUE seed_val){
  afrandomenginestruct* output = ALLOC(afrandomenginestruct);
  af_random_engine_type rtype = arf_randome_engine_type_from_rbsymbol(type_val);

  af_err flag = af_create_random_engine(&output->cengine, AF_RANDOM_ENGINE_DEFAULT, NUM2ULL(seed_val) ) ;

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Data_Wrap_Struct(Random, NULL, arf_engine_free, output);
}

static VALUE arf_retain_random_engine(VALUE self, VALUE engine_val){
  afrandomenginestruct* output = ALLOC(afrandomenginestruct);
  afrandomenginestruct* engine;

  Data_Get_Struct(engine_val, afrandomenginestruct, engine);

  af_err flag = af_retain_random_engine ( &output->cengine, engine->cengine);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Data_Wrap_Struct(Random, NULL, arf_engine_free, output);
}

static VALUE arf_random_engine_set_type(VALUE self, VALUE engine_val, VALUE type_val){
  af_random_engine_type rtype = arf_randome_engine_type_from_rbsymbol(type_val);
  afrandomenginestruct* engine;

  Data_Get_Struct(engine_val, afrandomenginestruct, engine);

  af_err flag = af_random_engine_set_type(&engine->cengine, rtype);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Qtrue;
}

static VALUE arf_random_engine_get_type(VALUE self, VALUE engine_val){
  af_random_engine_type rtype;
  afrandomenginestruct* engine;

  Data_Get_Struct(engine_val, afrandomenginestruct, engine);

  af_err flag = af_random_engine_get_type(&rtype, engine->cengine);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  const char* rengine = get_random_engine_name(rtype);
  return rb_str_new_cstr(rengine);
}

static VALUE arf_random_uniform(VALUE self, VALUE ndims_val, VALUE dim_val, VALUE engine_val){
  afstruct* out_array = ALLOC(afstruct);
  afrandomenginestruct* engine;

  Data_Get_Struct(engine_val, afrandomenginestruct, engine);

  dim_t ndims = (dim_t)FIX2LONG(ndims_val);
  dim_t* dimensions = ALLOC_N(dim_t, ndims);
  dim_t count = 1;
  for (dim_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(dim_val, index));
    count *= dimensions[index];
  }

  af_err flag = af_random_uniform(&out_array->carray, ndims, dimensions, f32, engine->cengine);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, out_array);
}

static VALUE arf_random_normal(VALUE self, VALUE ndims_val, VALUE dim_val, VALUE engine_val){
  afstruct* out_array = ALLOC(afstruct);
  afrandomenginestruct* engine;

  Data_Get_Struct(engine_val, afrandomenginestruct, engine);

  dim_t ndims = (dim_t)FIX2LONG(ndims_val);
  dim_t* dimensions = ALLOC_N(dim_t, ndims);
  dim_t count = 1;
  for (dim_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(dim_val, index));
    count *= dimensions[index];
  }

  af_err flag = af_random_uniform(&out_array->carray, ndims, dimensions, f32, engine->cengine);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, out_array);
}

static VALUE arf_random_engine_set_seed(VALUE self, VALUE engine_val ,VALUE seed_val){
  afrandomenginestruct* engine;

  Data_Get_Struct(engine_val, afrandomenginestruct, engine);

  af_err flag = af_random_engine_set_seed (&engine->cengine, NUM2ULL(seed_val));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Data_Wrap_Struct(Random, NULL, arf_engine_free, engine);
}

static VALUE arf_get_default_random_engine(VALUE self){
  afrandomenginestruct* output = ALLOC(afrandomenginestruct);

  af_err flag = af_get_default_random_engine(&output->cengine) ;

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Data_Wrap_Struct(Random, NULL, arf_engine_free, output);
}

static VALUE arf_set_default_random_engine_type(VALUE self, VALUE type_val){
  af_random_engine_type rtype = arf_randome_engine_type_from_rbsymbol(type_val);

  af_err flag = af_set_default_random_engine_type(rtype);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Qtrue;
}

static VALUE arf_random_engine_get_seed(VALUE self, VALUE engine_val){
  afrandomenginestruct* engine;
  uintl seed;

  Data_Get_Struct(engine_val, afrandomenginestruct, engine);

  af_err flag = af_random_engine_get_seed(&seed, engine->cengine);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return ULL2NUM(seed);
}

static VALUE arf_release_random_engine(VALUE self, VALUE engine_val){
  afrandomenginestruct* engine;

  Data_Get_Struct(engine_val, afrandomenginestruct, engine);

  af_err flag = af_release_random_engine(engine);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Qtrue;
}

static VALUE arf_randu(VALUE self, VALUE ndims_val, VALUE dim_val){
  afstruct* out_array = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(ndims_val);
  dim_t* dimensions = ALLOC_N(dim_t, ndims);
  dim_t count = 1;
  for (dim_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(dim_val, index));
    count *= dimensions[index];
  }

  af_err flag = af_randu(&out_array->carray, ndims, dimensions,f32);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, out_array);
}

static VALUE arf_randn(VALUE self, VALUE ndims_val, VALUE dim_val){
  afstruct* out_array = ALLOC(afstruct);

  dim_t ndims = (dim_t)FIX2LONG(ndims_val);
  dim_t* dimensions = ALLOC_N(dim_t, ndims);
  dim_t count = 1;
  for (dim_t index = 0; index < ndims; index++) {
    dimensions[index] = (dim_t)FIX2LONG(RARRAY_AREF(dim_val, index));
    count *= dimensions[index];
  }

  af_err flag = af_randn(&out_array->carray, ndims, dimensions,f32);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Data_Wrap_Struct(Af_Array, NULL, arf_free, out_array);
}

static VALUE arf_set_seed(VALUE self, VALUE seed){
  af_err flag = af_set_seed(NUM2ULL(seed));

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return Qtrue;
}

static VALUE arf_get_seed(VALUE self){
  uintl seed;

  af_err flag = af_get_seed(&seed);

  if (flag != AF_SUCCESS) arf_handle_exception(flag);

  return ULL2NUM(seed);
}
