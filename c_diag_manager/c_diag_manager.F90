module c_diag_manager_mod

  use FMS, only : fms_diag_init, fms_diag_end
  use FMS, only : fms_diag_register_diag_field, fms_diag_register_static_field, fms_diag_axis_init
  use FMS, only : fms_diag_send_data, fms_diag_send_complete, fms_diag_set_time_end
  use FMS, only : DIAG_OTHER, DIAG_OCEAN, DIAG_ALL

  use fms_diag_yaml_mod, only: get_num_unique_fields

  use FMS, only : fms_string_utils_c2f_string, fms_string_utils_f2c_string

  use FMS, only : FmsTime_type, Operator(+)
  use FMS, only : fms_time_manager_set_date, fms_time_manager_set_time

  use FMS, only : fms_mpp_error, FATAL
  use FMS, only : fms_time_manager_get_date

  use FMS, only : FmsMppDomain2D

  use c_fms_mod, only : cFMS_get_domain
  use c_fms_mod, only : NAME_LENGTH, MESSAGE_LENGTH
  use c_fms_utils_mod, only : cFMS_pointer_to_array

  use iso_c_binding

  implicit none

  private

  public :: cFMS_diag_axis_init_cfloat
  public :: cFMS_diag_axis_init_cdouble
  public :: cFMS_diag_end
  public :: cFMS_diag_send_complete
  public :: cFMS_diag_init
  public :: cFMS_diag_set_time_end

  public :: cFMS_register_diag_field_scalar_cint
  public :: cFMS_register_diag_field_scalar_cfloat
  public :: cFMS_register_diag_field_scalar_cdouble
  public :: cFMS_register_diag_field_array_cint
  public :: cFMS_register_diag_field_array_cfloat
  public :: cFMS_register_diag_field_array_cdouble

  public :: cFMS_diag_send_data_2d_cint
  public :: cFMS_diag_send_data_3d_cint
  public :: cFMS_diag_send_data_4d_cint
  public :: cFMS_diag_send_data_2d_cfloat
  public :: cFMS_diag_send_data_3d_cfloat
  public :: cFMS_diag_send_data_4d_cfloat
  public :: cFMS_diag_send_data_2d_cdouble
  public :: cFMS_diag_send_data_3d_cdouble
  public :: cFMS_diag_send_data_4d_cdouble

  integer, public, bind(C, name="DIAG_OTHER") :: DIAG_OTHER_C = DIAG_OTHER
  integer, public, bind(C, name="DIAG_OCEAN") :: DIAG_OCEAN_C = DIAG_OCEAN
  integer, public, bind(C, name="DIAG_ALL")   :: DIAG_ALL_C   = DIAG_ALL

contains

  subroutine cFMS_diag_end(time_end) bind(C, name="cFMS_diag_end")
    implicit none
    integer, intent(in) :: time_end(7) !< year, month, date, hours, minutes, seconds, ticks
    type(FmsTime_type) :: model_end_time

    model_end_time = fms_time_manager_set_date(year = time_end(1),   &
                                         month= time_end(2),   &
                                         day = time_end(3),    &
                                         hour = time_end(4),   &
                                         minute = time_end(5), &
                                         second = time_end(6), &
                                         tick = time_end(7))
    call fms_diag_end(model_end_time)

  end subroutine cFMS_diag_end

  !cFMS_diag_init
  subroutine cFMS_diag_init(diag_model_subset, time_init, err_msg) bind(C, name='cFMS_diag_init')

    implicit none
    integer, intent(in), optional :: diag_model_subset
    integer, intent(in), optional :: time_init(6)
    character(c_char), intent(out), optional :: err_msg(MESSAGE_LENGTH)

    character(len=MESSAGE_LENGTH-1) :: err_msg_f = "None"

    call fms_diag_init(diag_model_subset = diag_model_subset, &
                       time_init = time_init, &
                       err_msg = err_msg_f)

    if(present(err_msg) .and. err_msg_f /= '' ) call fms_string_utils_f2c_string(err_msg, err_msg_f)

  end subroutine cFMS_diag_init

  !cFMS_diag_send_complete
  subroutine cFMS_diag_send_complete(timestep, err_msg) bind(C, name="cFMS_diag_send_complete")

    implicit none
    integer, intent(in) :: timestep(7)
    character(c_char), intent(out), optional :: err_msg(MESSAGE_LENGTH)
    type(FmsTime_type) :: time

    character(len=MESSAGE_LENGTH-1) :: err_msg_f = "None"

    time = fms_time_manager_set_date(year=timestep(1),   &
                                           month=timestep(2),  &
                                           day=timestep(3),    &
                                           hour=timestep(4),   &
                                           minute=timestep(5), &
                                           second=timestep(6), &
                                           tick=timestep(7))
    call fms_diag_send_complete(time, err_msg_f)

    if(present(err_msg) .and. err_msg_f /= '' ) call fms_string_utils_f2c_string(err_msg, err_msg_f)

  end subroutine cFMS_diag_send_complete

  subroutine cFMS_diag_set_time_end(time_end, err_msg) &
       bind(C, name="cFMS_diag_set_time_end")

    implicit none
    integer, intent(in), optional :: time_end(7)
    character(c_char), intent(in), optional :: err_msg(MESSAGE_LENGTH)

    character(MESSAGE_LENGTH-1) :: err_msg_f
    type(FmsTime_type) :: time

    time = fms_time_manager_set_date(year = time_end(1),     &
                                                   month = time_end(2),   &
                                                   day = time_end(3),       &
                                                   hour = time_end(4),     &
                                                   minute = time_end(5), &
                                                   second = time_end(6), &
                                                   tick = time_end(7),     &
                                                   err_msg = err_msg_f)

    call fms_diag_set_time_end(time)

  end subroutine cFMS_diag_set_time_end


#include "c_diag_axis_init.fh"
#include "c_register_diag_field.fh"
#include "c_send_data.fh"

end module c_diag_manager_mod
