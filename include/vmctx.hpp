#pragma once
#include <vmutils.hpp>

namespace vm {
class vmctx_t {
 public:
  explicit vmctx_t(std::uintptr_t module_base,
                   std::uintptr_t image_base,
                   std::uintptr_t image_size,
                   std::uintptr_t vm_entry_rva);
  bool init();
  const std::uintptr_t m_module_base, m_image_base, m_vm_entry_rva,
      m_image_size;

  zydis_register_t get_vip() const { return m_vip; }
  zydis_register_t get_vsp() const { return m_vsp; }
  zydis_routine_t get_vm_enter() const { return m_vm_entry; }

 private:
  /// <summary>
  /// m_vip and m_vsp are set to the native registers used for them by the vm
  /// enter... these will change during the execution inside of the vm but these
  /// values stay the same as the ones used by vm enter...
  /// </summary>
  zydis_register_t m_vip, m_vsp;

  /// <summary>
  /// the virtual machine enter flattened and deobfuscated...
  /// </summary>
  zydis_routine_t m_vm_entry;
};
}  // namespace vm