function CFMS_REGISTER_DIAG_FIELD_SCALAR_(module_name, field_name, long_name, units, time,              &
     missing_value, range, standard_name, do_not_log, err_msg, area, volume, realm, multiple_send_data) &
     bind(C, name=CFMS_REGISTER_DIAG_FIELD_SCALAR_BINDC_)

  implicit none
  character(c_char), intent(in) :: module_name(NAME_LENGTH)
  character(c_char), intent(in) :: field_name(NAME_LENGTH)
  character(c_char), intent(in),  optional :: long_name(NAME_LENGTH)
  character(c_char), intent(in),  optional :: units(NAME_LENGTH)
  integer(c_int), intent(in), optional :: time(7) !< year, month, date, hours, minutes, seconds, ticks
  character(c_char), intent(in),  optional :: standard_name(NAME_LENGTH)
  CFMS_REGISTER_DIAG_FIELD_SCALAR_TYPE_, intent(in), optional :: missing_value
  CFMS_REGISTER_DIAG_FIELD_SCALAR_TYPE_, intent(in), optional :: range(2)
  logical(c_bool),   intent(in),  optional :: do_not_log
  character(c_char), intent(out), optional :: err_msg(NAME_LENGTH)
  integer,           intent(in),  optional :: area
  integer,           intent(in),  optional :: volume
  character(c_char), intent(in),  optional :: realm(NAME_LENGTH)
  logical(c_bool),   intent(in),  optional :: multiple_send_data

  character(len=NAME_LENGTH-1) :: module_name_f    = ''
  character(len=NAME_LENGTH-1) :: field_name_f     = ''
  character(len=NAME_LENGTH-1) :: long_name_f      = ''
  character(len=NAME_LENGTH-1) :: standard_name_f  = ''
  character(len=NAME_LENGTH-1) :: units_f   = ''
  character(len=NAME_LENGTH-1) :: err_msg_f = ''
  character(len=NAME_LENGTH-1) :: realm_f   = ''

  logical :: do_not_log_f
  logical :: multiple_send_data_f
  integer :: CFMS_REGISTER_DIAG_FIELD_SCALAR_

  type(FmsTime_type) :: field_init_time

  module_name_f = ''
  field_name_f = ''
  long_name_f = ''
  standard_name_f = ''
  units_f = ''
  err_msg_f = ''
  realm_f = ''

  do_not_log_f = .False.
  multiple_send_data_f = .False.

  if(present(do_not_log)) do_not_log_f = logical(do_not_log)
  if(present(multiple_send_data)) multiple_send_data_f = logical(multiple_send_data)

  module_name_f = fms_string_utils_c2f_string(module_name)
  field_name_f  = fms_string_utils_c2f_string(field_name)
  if(present(units))     units_f = fms_string_utils_c2f_string(units)
  if(present(realm))     realm_f = fms_string_utils_c2f_string(realm)
  if(present(long_name)) long_name_f = fms_string_utils_c2f_string(long_name)
  if(present(standard_name)) standard_name_f = fms_string_utils_c2f_string(standard_name)
  if(present(time)) then
    field_init_time = fms_time_manager_set_date(year=time(1),   &
                                           month=time(2),  &
                                           day=time(3),    &
                                           hour=time(4),   &
                                           minute=time(5), &
                                           second=time(6), &
                                           tick=time(7))
  endif

  CFMS_REGISTER_DIAG_FIELD_SCALAR_ = fms_diag_register_diag_field(module_name_f,                   &
                                                                  field_name_f,                    &
                                                                  init_time = field_init_time,     &
                                                                  long_name = long_name_f,         &
                                                                  units = units_f,                 &
                                                                  missing_value = missing_value,   &
                                                                  range = range,                   &
                                                                  standard_name = standard_name_f, &
                                                                  do_not_log = do_not_log_f,       &
                                                                  err_msg = err_msg_f,             &
                                                                  area = area,                     &
                                                                  volume = volume,                 &
                                                                  realm = realm_f,                 &
                                                                  multiple_send_data = multiple_send_data_f)

  if(present(err_msg) .and. err_msg_f /= '') call fms_string_utils_f2c_string(err_msg, err_msg_f)

end function CFMS_REGISTER_DIAG_FIELD_SCALAR_


function CFMS_REGISTER_DIAG_FIELD_ARRAY_(module_name, field_name, axes, long_name, units, time,      &
     missing_value, range, mask_variant, standard_name, verbose, do_not_log, err_msg, interp_method, &
     tile_count, area, volume, realm, multiple_send_data) bind(C, name=CFMS_REGISTER_DIAG_FIELD_ARRAY_BINDC_)

  implicit none
  character(c_char), intent(in) :: module_name(NAME_LENGTH)
  character(c_char), intent(in) :: field_name(NAME_LENGTH)
  integer,           intent(in), optional  :: axes(5)
  character(c_char), intent(in), optional  :: long_name(NAME_LENGTH)
  character(c_char), intent(in), optional  :: units(NAME_LENGTH)
  integer(c_int), intent(in), optional :: time(7) !< year, month, date, hours, minutes, seconds, ticks
  CFMS_REGISTER_DIAG_FIELD_ARRAY_TYPE_, intent(in), optional :: missing_value
  CFMS_REGISTER_DIAG_FIELD_ARRAY_TYPE_, intent(in), optional :: range(2)
  logical(c_bool),   intent(in), optional  :: mask_variant
  character(c_char), intent(in), optional  :: standard_name(NAME_LENGTH)
  logical(c_bool),   intent(in), optional  :: verbose
  logical(c_bool),   intent(in), optional  :: do_not_log
  character(c_char), intent(out), optional :: err_msg(MESSAGE_LENGTH)
  character(c_char), intent(in), optional  :: interp_method(NAME_LENGTH)
  integer,           intent(in), optional  :: tile_count
  integer,           intent(in), optional  :: area
  integer,           intent(in), optional  :: volume
  character(c_char), intent(in), optional  :: realm(NAME_LENGTH)
  logical(c_bool),   intent(in), optional  :: multiple_send_data

  character(len=NAME_LENGTH-1) :: module_name_f
  character(len=NAME_LENGTH-1) :: field_name_f
  character(len=NAME_LENGTH-1) :: long_name_f
  character(len=NAME_LENGTH-1) :: units_f
  character(len=NAME_LENGTH-1) :: standard_name_f
  character(len=NAME_LENGTH-1) :: err_msg_f
  character(len=NAME_LENGTH-1) :: interp_method_f
  character(len=NAME_LENGTH-1) :: realm_f

  logical :: mask_variant_f
  logical :: verbose_f
  logical :: do_not_log_f
  logical :: multiple_send_data_f
  integer :: naxes

  integer :: CFMS_REGISTER_DIAG_FIELD_ARRAY_
  type(FmsTime_type) :: field_init_time

  long_name_f = ''
  units_f = ''
  standard_name_f = ''
  interp_method_f = ''
  realm_f = ''

  mask_variant_f = .false.
  verbose_f = .false.
  do_not_log_f = .false.
  multiple_send_data_f = .false.

  module_name_f = fms_string_utils_c2f_string(module_name)
  field_name_f  = fms_string_utils_c2f_string(field_name)
  if(present(long_name))     long_name_f = fms_string_utils_c2f_string(long_name)
  if(present(units))         units_f = fms_string_utils_c2f_string(units)
  if(present(standard_name)) standard_name_f = fms_string_utils_c2f_string(standard_name)
  if(present(interp_method)) interp_method_f = fms_string_utils_c2f_string(interp_method)
  if(present(realm))         realm_f = fms_string_utils_c2f_string(realm)

  if(present(mask_variant)) mask_variant_f = logical(mask_variant)
  if(present(verbose)) verbose_f = logical(verbose)
  if(present(do_not_log)) do_not_log_f = logical(do_not_log)
  if(present(multiple_send_data)) multiple_send_data_f = logical(multiple_send_data)
  if(present(time)) then
    field_init_time = fms_time_manager_set_date(year=time(1),   &
                                           month=time(2),  &
                                           day=time(3),    &
                                           hour=time(4),   &
                                           minute=time(5), &
                                           second=time(6), &
                                           tick=time(7))
  endif

  if(present(axes)) then
     naxes = 5 - count(axes<=0)
     CFMS_REGISTER_DIAG_FIELD_ARRAY_ = fms_diag_register_diag_field(module_name = module_name_f,     &
                                                                    field_name = field_name_f,       &
                                                                    axes = axes(1:naxes),            &
                                                                    init_time = field_init_time,     &
                                                                    long_name = long_name_f,         &
                                                                    units = units_f,                 &
                                                                    missing_value = missing_value,   &
                                                                    range = range,                   &
                                                                    mask_variant = mask_variant_f,   &
                                                                    standard_name = standard_name_f, &
                                                                    verbose = verbose_f,             &
                                                                    do_not_log = do_not_log_f,       &
                                                                    err_msg = err_msg_f,             &
                                                                    interp_method = interp_method_f, &
                                                                    tile_count = tile_count,         &
                                                                    area = area,                     &
                                                                    volume = volume,                 &
                                                                    realm = realm_f,                 &
                                                                    multiple_send_data = multiple_send_data_f)
  else
     CFMS_REGISTER_DIAG_FIELD_ARRAY_ = fms_diag_register_diag_field(module_name_f,                        &
                                                                    field_name_f,                         &
                                                                    axes,                                 &
                                                                    init_time = field_init_time,          &
                                                                    long_name = long_name_f,              &
                                                                    units = units_f,                      &
                                                                    missing_value = missing_value,        &
                                                                    range = range,                        &
                                                                    mask_variant = logical(mask_variant), &
                                                                    standard_name = standard_name_f,      &
                                                                    verbose = logical(verbose),           &
                                                                    do_not_log = logical(do_not_log),     &
                                                                    err_msg = err_msg_f,                  &
                                                                    interp_method = interp_method_f,      &
                                                                    tile_count = tile_count,              &
                                                                    area = area,                          &
                                                                    volume = volume,                      &
                                                                    realm = realm_f,                      &
                                                                    multiple_send_data = logical(multiple_send_data))
  end if

end function CFMS_REGISTER_DIAG_FIELD_ARRAY_
