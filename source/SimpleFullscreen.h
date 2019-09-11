
#pragma once
#include <stdint.h>
#include "hydra_graphics.h"

// This file is autogenerated!
namespace SimpleFullscreen {

struct LocalConstantsUI {

	float					scale				= 32.000000f;
	float					modulo				= 2.000000f;

	void reflectMembers() {
		ImGui::InputScalar( "Scale", ImGuiDataType_Float, &scale);
		ImGui::InputScalar( "Modulo", ImGuiDataType_Float, &modulo);
	}

	void reflectUI() {
		ImGui::Begin( "LocalConstants" );
		reflectMembers();
		ImGui::End();
	}

}; // struct LocalConstantsUI

struct LocalConstants {

	float					scale				= 32.000000f;
	float					modulo				= 2.000000f;
	float					pad_tail[2];

}; // struct LocalConstants

struct LocalConstantsBuffer {

	hydra::graphics::BufferHandle	buffer;
	LocalConstants					constants;
	LocalConstantsUI				constantsUI;

	void create( hydra::graphics::Device& device ) {
		using namespace hydra;

		graphics::BufferCreation constants_creation = { graphics::BufferType::Constant, graphics::ResourceUsageType::Dynamic, sizeof( LocalConstants ), &constants, "LocalConstants" };
		buffer = device.create_buffer( constants_creation );
	}

	void destroy( hydra::graphics::Device& device ) {
		device.destroy_buffer( buffer );
	}

	void updateUI( hydra::graphics::Device& device ) {
		// Draw UI
		constantsUI.reflectUI();
		// Update constants from UI
		hydra::graphics::MapBufferParameters map_parameters = { buffer.handle, 0, 0 };
		LocalConstants* buffer_data = (LocalConstants*)device.map_buffer( map_parameters );
		if (buffer_data) {
			buffer_data->scale = constantsUI.scale;
			buffer_data->modulo = constantsUI.modulo;
			device.unmap_buffer( map_parameters );
		}
	}
}; // struct LocalConstantBuffer

} // namespace SimpleFullscreen

