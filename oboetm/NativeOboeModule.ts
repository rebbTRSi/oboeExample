import { TurboModule, TurboModuleRegistry } from "react-native";

export interface Spec extends TurboModule {
    readonly initOboe: () => void;
}

export default TurboModuleRegistry.get<Spec>("NativeOboeModule") as Spec | null;