module tagarray_utils
  use, intrinsic :: iso_c_binding, only: c_int8_t, c_int16_t, c_int32_t, c_int64_t, &
                                         c_float, c_double, c_float_complex, c_double_complex, &
                                         c_ptr, c_loc
  use tagarray_defines
  implicit none
  private
  interface to_Cstring
    module procedure :: str_to_Cstr
  end interface to_Cstring
  interface get_type_id
    module procedure :: get_type_id_scalar, get_type_id_array
  end interface get_type_id
  public to_Cstring, get_type_id, get_storage_size
contains
  function str_to_Cstr(string) result(Cstring)
    character(kind=TAGARRAY_CHAR, len=*), intent(in) :: string
    character(kind=TAGARRAY_CHAR, len=:), allocatable :: Cstring
    integer :: last
    Cstring = trim(adjustl(string))
    last = len(Cstring)
    if (last == 0) then
      deallocate(Cstring)
      allocate(character(kind=TAGARRAY_CHAR, len=1) :: Cstring)
      Cstring(1:1) = char(0, kind=TAGARRAY_CHAR)
      last = 1
    end if
    if (Cstring(last:last) /= char(0, kind=TAGARRAY_CHAR)) then
      Cstring = Cstring // char(0, kind=TAGARRAY_CHAR)
    end if
  end function str_to_Cstr
  integer(c_int32_t) function get_type_id_array(values) result(type_id)
    class(*), target, intent(in) :: values(*)
    class(*), pointer :: value
    value => values(1)
    type_id = get_type_id_scalar(value)
  end function get_type_id_array
  integer(c_int32_t) function get_type_id_scalar(value) result(type_id)
    class(*), target, intent(in) :: value
    type_id = TAGARRAY_TYPE_UNKNOWN
    select type (value)
      type is (integer(c_int8_t))
        type_id = TAGARRAY_TYPE_INT8
      type is (integer(c_int16_t))
        type_id = TAGARRAY_TYPE_INT16
      type is (integer(c_int32_t))
        type_id = TAGARRAY_TYPE_INT32
      type is (integer(c_int64_t))
        type_id = TAGARRAY_TYPE_INT64
      type is (real(c_float))
        type_id = TAGARRAY_TYPE_REAL32
      type is (real(c_double))
        type_id = TAGARRAY_TYPE_REAL64
      type is (complex(c_float_complex))
        type_id = TAGARRAY_TYPE_CMPLX32
      type is (complex(c_double_complex))
        type_id = TAGARRAY_TYPE_CMPLX64
      type is (character(kind=TAGARRAY_CHAR, len=*))
        type_id = TAGARRAY_TYPE_CHAR8
      class default
        type_id = TAGARRAY_TYPE_UNKNOWN
    end select
  end function get_type_id_scalar
  integer(c_int64_t) function get_storage_size(datatype) result(size)
    integer(c_int32_t) :: datatype
    select case(datatype)
      case (TAGARRAY_TYPE_UNKNOWN)
        size = 1
      case (TAGARRAY_TYPE_INT8)
        size = 1
      case (TAGARRAY_TYPE_INT16)
        size = 2
      case (TAGARRAY_TYPE_INT32)
        size = 4
      case (TAGARRAY_TYPE_INT64)
        size = 8
      case (TAGARRAY_TYPE_UINT8)
        size = 1
      case (TAGARRAY_TYPE_UINT16)
        size = 2
      case (TAGARRAY_TYPE_UINT32)
        size = 4
      case (TAGARRAY_TYPE_UINT64)
        size = 8
      case (TAGARRAY_TYPE_REAL32)
        size = 4
      case (TAGARRAY_TYPE_REAL64)
        size = 8
      case (TAGARRAY_TYPE_CMPLX32)
        size = 8
      case (TAGARRAY_TYPE_CMPLX64)
        size = 16
      case default
        size = 1
    end select
  end function get_storage_size
end module tagarray_utils
