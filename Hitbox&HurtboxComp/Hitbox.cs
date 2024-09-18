using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public enum ColliderState {
    Closed,
    Open,
    Colliding
}
public class Hitbox : MonoBehaviour
{
    [Header("GIZMOS COLORS")]
    public bool isGizmosEnabled = true;
    public Color inactiveColor;
    public Color collisionOpenColor;
    public Color collidingColor;
    [SerializeField] private Vector3 _boxSize;
    [SerializeField] private Transform _transform;
    [SerializeField] private LayerMask _mask;
    private ColliderState _state;
    private IHitboxResponder _responder = null;

    private void Start() {
        StartCheckingCollision();
    }
    private void Update() {
        HitboxUpdate();
    }
    void HitboxUpdate(){
        if (_state == ColliderState.Closed) { return; }

        Collider[] colliders = Physics.OverlapBox(_transform.position, _boxSize, _transform.rotation, _mask);
        
        for (int i = 0; i < colliders.Length; i++) {
            Collider aCollider = colliders[i];
            _responder?.CollidedWith(aCollider);
        }
        _state = colliders.Length > 0 ? ColliderState.Colliding : ColliderState.Open;
    }

    public void StartCheckingCollision(){
        _state = ColliderState.Open;
    }

    public void StopCheckingCollision(){
        _state = ColliderState.Closed;
    }

    public void SetResponder(IHitboxResponder responder){
        _responder = responder;
    }

    private void OnDrawGizmos(){
        if (!isGizmosEnabled){
            return;
        }
        CheckGizmoColor();
        Gizmos.matrix = Matrix4x4.TRS(transform.position, transform.rotation, transform.localScale);
        Gizmos.DrawCube(Vector3.zero, new Vector3(_boxSize.x * 2, _boxSize.y * 2, _boxSize.z * 2)); 

    }
    private void CheckGizmoColor()
    {
        switch (_state)
        {
            case ColliderState.Closed:
                Gizmos.color = inactiveColor;
                break;
            case ColliderState.Open:
                Gizmos.color = collisionOpenColor;
                break;
            case ColliderState.Colliding:
                Gizmos.color = collidingColor;
                break;
        }
    }

}
